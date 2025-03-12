#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <HardwareSerial.h>

#define LED_PIN 5
#define NUM_LEDS 10
#define STEPPER_TX 7 // ESP32 TX to Stepper PCB RX
#define PM25_SENSOR_PIN 36 // Mock sensor input for PM2.5

// Initialize LED strip
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
HardwareSerial stepperSerial(1);

// BLE Setup
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
String receivedData = "";

class MovingAverageFilter {
  private:
    float buffer[5];
    int index = 0;
  public:
    MovingAverageFilter() {
      memset(buffer, 0, sizeof(buffer));
    }
    float update(float value) {
      buffer[index] = value;
      index = (index + 1) % 5;
      float sum = 0;
      for (int i = 0; i < 5; i++) sum += buffer[i];
      return sum / 5;
    }
};
MovingAverageFilter pm25_filter;

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      receivedData = String(value.c_str());
    }
  }
};

void setup() {
  Serial.begin(115200);
  stepperSerial.begin(9600, SERIAL_8N1, STEPPER_TX, -1);
  strip.begin();
  strip.show();
  pinMode(PM25_SENSOR_PIN, INPUT);

  BLEDevice::init("Air Quality Display");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x181A));
  pCharacteristic = pService->createCharacteristic(
      BLEUUID((uint16_t)0x2A6E), 
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  BLEDevice::startAdvertising();
}

void update_leds(int pm25_value) {
  if (pm25_value < 50) strip.fill(strip.Color(0, 255, 0));
  else if (pm25_value < 100) strip.fill(strip.Color(255, 165, 0));
  else strip.fill(strip.Color(255, 0, 0));
  strip.show();
}

void update_stepper(int pm25_value) {
  int stepperPosition = map(pm25_value, 0, 500, 0, 315);
  stepperSerial.print(stepperPosition);
}

int read_pm25() {
  int raw_value = analogRead(PM25_SENSOR_PIN);
  float scaled_value = (raw_value / 4095.0) * 500.0;
  return pm25_filter.update(scaled_value);
}

void loop() {
  int pm25_value = read_pm25();
  pCharacteristic->setValue(String(pm25_value).c_str());
  pCharacteristic->notify();
  update_stepper(pm25_value);
  update_leds(pm25_value);
  delay(2000);
}

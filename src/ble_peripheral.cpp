#include "ble_peripheral.h"

BLEPeripheral::BLEPeripheral(const char* name) {
    BLEDevice::init(name);
    pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(serviceUUID);
    pCharacteristic = pService->createCharacteristic(
        charUUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUUID);
    BLEDevice::startAdvertising();
}

void BLEPeripheral::send(float value) {
    char buffer[8];
    dtostrf(value, 6, 2, buffer);
    pCharacteristic->setValue(buffer);
    pCharacteristic->notify();
}

void BLEPeripheral::set_callback(void (*cb)(float)) {
    callback = cb;
    pCharacteristic->setCallbacks(new BLECharacteristicCallbacks());
}

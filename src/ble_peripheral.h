#ifndef BLE_PERIPHERAL_H
#define BLE_PERIPHERAL_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLEPeripheral {
private:
    BLEServer *pServer;
    BLECharacteristic *pCharacteristic;
    std::string serviceUUID = "181A";
    std::string charUUID = "2A6E";
    void (*callback)(float);

public:
    BLEPeripheral(const char* name = "AirQualityMonitor");
    void send(float value);
    void set_callback(void (*cb)(float));
};

#endif

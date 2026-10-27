#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class RfidReader {
public:
    RfidReader();
    void begin();
    bool scan(char* uidOut, size_t uidOutSize);

private:
    MFRC522 mfrc522;
};

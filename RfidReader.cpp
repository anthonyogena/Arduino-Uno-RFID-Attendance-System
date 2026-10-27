#include "RfidReader.h"
#include "config.h"

RfidReader::RfidReader() : mfrc522(RFID_CS_PIN, RFID_RST_PIN) {}

void RfidReader::begin() {
    // Initialize the RFID reader hardware.
    SPI.begin();
    mfrc522.PCD_Init();
}

bool RfidReader::scan(char* uidOut, size_t uidOutSize) {
    // Poll for a new card and read its UID.
    if (!mfrc522.PICC_IsNewCardPresent()) return false;
    if (!mfrc522.PICC_ReadCardSerial()) return false;

    // Convert UID bytes to a hex string.
    int len = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (len + 2 < (int)uidOutSize) {
            len += snprintf(uidOut + len, uidOutSize - len, "%02X", mfrc522.uid.uidByte[i]);
        }
    }
    uidOut[len] = '\0';

    // Halt the card to stop transmission.
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    return true;
}

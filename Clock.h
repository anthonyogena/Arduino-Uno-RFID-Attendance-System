#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

class Clock {
public:
    Clock();
    // Initialize the DS3231 RTC over I2C.
    void begin();
    // Write the current date/time into buf as "YYYY-MM-DD HH:MM:SS".
    bool now(char* buf, size_t bufSize);
    // Report whether the RTC initialized successfully.
    bool ready() const;

private:
    RTC_DS3231 rtc;
    bool _ready;
};

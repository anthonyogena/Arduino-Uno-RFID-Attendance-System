#include "Clock.h"
#include "config.h"

Clock::Clock() : _ready(false) {}

void Clock::begin() {
    // Start I2C and probe the DS3231; mark ready if it responds.
    Wire.begin();
    if (rtc.begin()) {
        _ready = true;
    }
}

bool Clock::now(char* buf, size_t bufSize) {
    // Format the current RTC time into buf; return false if not ready.
    if (!_ready) {
        snprintf(buf, bufSize, "%s", "N/A");
        return false;
    }
    DateTime t = rtc.now();
    snprintf(buf, bufSize, "%04d-%02d-%02d %02d:%02d:%02d",
             t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second());
    return true;
}

bool Clock::ready() const {
    // Report whether the RTC initialized successfully.
    return _ready;
}

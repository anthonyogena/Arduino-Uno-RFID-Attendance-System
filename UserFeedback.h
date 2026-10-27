#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class UserFeedback {
public:
    UserFeedback();
    // Initialize the LCD and show the idle prompt.
    void begin();
    // Show the idle prompt on the LCD.
    void showIdle();
    // Show success message with student name.
    void showSuccess(const char* name);
    // Show unknown card message.
    void showUnknown();
    // Show already recorded message.
    void showAlreadyRecorded();
    // Non-blocking idle timeout; returns true if display state changed.
    bool tick();

private:
    LiquidCrystal_I2C lcd;
    unsigned long _msgStart;
    bool _msgActive;
    void _show(const __FlashStringHelper* line1, const char* line2);
};

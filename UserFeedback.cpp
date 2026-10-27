#include "UserFeedback.h"
#include "config.h"

UserFeedback::UserFeedback() : lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS), _msgStart(0), _msgActive(false) {}

void UserFeedback::begin() {
    // Initialize the LCD, turn on backlight, and show idle prompt.
    lcd.init();
    lcd.backlight();
    showIdle();
}

void UserFeedback::showIdle() {
    // Return to the idle "Tap card" prompt.
    _msgActive = false;
    _show(F("Tap card"), nullptr);
}

void UserFeedback::showSuccess(const char* name) {
    // Show success message with the student name.
    _msgActive = true;
    _msgStart = millis();
    _show(F("Success"), name);
}

void UserFeedback::showUnknown() {
    // Show unknown card message.
    _msgActive = true;
    _msgStart = millis();
    _show(F("Unknown card"), nullptr);
}

void UserFeedback::showAlreadyRecorded() {
    // Show duplicate scan message.
    _msgActive = true;
    _msgStart = millis();
    _show(F("Already recorded"), nullptr);
}

bool UserFeedback::tick() {
    // Return to idle after the idle timeout elapses.
    if (_msgActive && millis() - _msgStart >= IDLE_TIMEOUT_MS) {
        showIdle();
        return true;
    }
    return false;
}

void UserFeedback::_show(const __FlashStringHelper* line1, const char* line2) {
    // Clear and write two lines to the LCD.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    if (line2 && line2[0]) {
        lcd.print(line2);
    } else {
        lcd.print(F("                "));
    }
}

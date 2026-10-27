#include <Arduino.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "RfidReader.h"
#include "Clock.h"
#include "StudentRegistry.h"
#include "AttendanceLogger.h"
#include "UserFeedback.h"

RfidReader rfid;
Clock clock;
UserFeedback feedback;

unsigned long lastScanTime = 0;
unsigned long feedbackStartTime = 0;
bool feedbackActive = false;

void setup() {
    // Initialize serial, output pins, RFID reader, RTC clock, SD logger, and LCD feedback.
    Serial.begin(SERIAL_BAUD);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    rfid.begin();
    clock.begin();
    attendanceLoggerBegin();
    feedback.begin();

    Serial.println(F("RFID Attendance System Ready"));
    Serial.println(F("Tap a card to scan."));
}

void loop() {
    unsigned long now = millis();

    // Handle non-blocking LCD idle timeout.
    feedback.tick();

    // Enforce scan cooldown.
    if (now - lastScanTime < SCAN_COOLDOWN_MS) {
        return;
    }

    char uid[UID_HEX_BUFFER_SIZE] = {0};
    if (rfid.scan(uid, sizeof(uid))) {
        lastScanTime = now;

        char ts[20];
        clock.now(ts, sizeof(ts));

        uint8_t idx = findStudentByUid(uid);

        if (idx < MAX_STUDENTS) {
            bool logged = logAttendance(idx, ts);
            Serial.print(F("Card UID: "));
            Serial.print(uid);
            Serial.print(F(" | Time: "));
            Serial.print(ts);
            Serial.println(logged ? F(" | Logged") : F(" | Already recorded today"));

            if (logged) {
                char name[17];
                strcpy_P(name, (PGM_P)&students[idx].name);
                feedback.showSuccess(name);
                digitalWrite(GREEN_LED_PIN, HIGH);
            } else {
                feedback.showAlreadyRecorded();
                digitalWrite(RED_LED_PIN, HIGH);
            }
            digitalWrite(BUZZER_PIN, HIGH);
        } else {
            Serial.print(F("Card UID: "));
            Serial.print(uid);
            Serial.print(F(" | Time: "));
            Serial.println(ts);
            Serial.println(F("Unknown card"));

            feedback.showUnknown();
            digitalWrite(RED_LED_PIN, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
        }

        feedbackActive = true;
        feedbackStartTime = now;
    }

    // Deactivate LED/buzzer feedback after FEEDBACK_MS.
    if (feedbackActive && now - feedbackStartTime >= FEEDBACK_MS) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        feedbackActive = false;
    }
}

#include "AttendanceLogger.h"
#include "config.h"
#include "StudentRegistry.h"
#include <avr/pgmspace.h>

static File logFile;
static uint16_t _lastDate[MAX_STUDENTS] = {0};
static bool _sdReady = false;

bool attendanceLoggerBegin() {
    // Initialize SD card and create CSV header if file does not exist.
    if (!SD.begin(SD_CS_PIN)) {
        _sdReady = false;
        return false;
    }
    _sdReady = true;
    if (!SD.exists(LOG_FILE_NAME)) {
        logFile = SD.open(LOG_FILE_NAME, FILE_WRITE);
        if (logFile) {
            logFile.println(F("UID,Student ID,Name,Date,Time"));
            logFile.close();
        }
    }
    return _sdReady;
}

bool logAttendance(uint8_t studentIndex, const char* timestamp) {
    // Append CSV row if student not already logged today; return false on duplicate.
    if (!_sdReady || studentIndex >= MAX_STUDENTS) return false;

    // Extract MMDD date key from "YYYY-MM-DD HH:MM:SS".
    uint16_t dateKey = ((timestamp[6] - '0') * 10 + (timestamp[7] - '0')) * 100;
    dateKey += (timestamp[8] - '0') * 10 + (timestamp[9] - '0');

    if (_lastDate[studentIndex] == dateKey) return false;
    _lastDate[studentIndex] = dateKey;

    // Read student fields from PROGMEM into RAM.
    char uid[15];
    char id[10];
    char name[17];
    strcpy_P(uid, (PGM_P)&students[studentIndex].uid);
    strcpy_P(id, (PGM_P)&students[studentIndex].id);
    strcpy_P(name, (PGM_P)&students[studentIndex].name);

    // Direct write to SD without intermediate line buffer.
    logFile = SD.open(LOG_FILE_NAME, FILE_WRITE);
    if (!logFile) return false;
    logFile.print(uid);
    logFile.print(F(","));
    logFile.print(id);
    logFile.print(F(","));
    logFile.print(name);
    logFile.print(F(","));
    logFile.print(timestamp);
    logFile.println();
    logFile.close();
    return true;
}

#include "StudentRegistry.h"
#include <avr/pgmspace.h>

const Student students[] PROGMEM = {
    {"A1B2C3D4", "S001", "Alice Johnson"},
    {"E5F6A7B8", "S002", "Bob Smith"},
    {"C9D0E1F2", "S003", "Carol Lee"},
    {"00000000", "S004", "Dan Brown"},
    {"11111111", "S005", "Eva Green"}
};

const uint8_t studentCount = 5;

int findStudentByUid(const char* uid) {
    // Scan PROGMEM student table for matching UID; return index or -1.
    for (uint8_t i = 0; i < studentCount; i++) {
        char storedUid[15];
        strcpy_P(storedUid, (PGM_P)&students[i].uid);
        if (strcmp(uid, storedUid) == 0) return i;
    }
    return -1;
}

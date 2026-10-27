#pragma once

#include <Arduino.h>
#include <avr/pgmspace.h>

struct Student {
    char uid[15];
    char id[10];
    char name[17];
};

extern const Student students[] PROGMEM;
extern const uint8_t studentCount;

int findStudentByUid(const char* uid);

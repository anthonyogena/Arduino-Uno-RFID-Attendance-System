#pragma once

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#define LOG_FILE_NAME "ATT.CSV"
#define MAX_STUDENTS 5

bool attendanceLoggerBegin();
bool logAttendance(uint8_t studentIndex, const char* timestamp);

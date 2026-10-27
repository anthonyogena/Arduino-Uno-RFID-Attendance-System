#pragma once

#include <Arduino.h>

// Pin map
#define RFID_CS_PIN     10
#define RFID_RST_PIN     9
#define SD_CS_PIN       4
#define GREEN_LED_PIN   7
#define RED_LED_PIN     8
#define BUZZER_PIN      6

// LCD I2C
#define LCD_I2C_ADDR   0x27
#define LCD_COLS       16
#define LCD_ROWS        2

// Buffer sizes
#define UID_HEX_BUFFER_SIZE 21

// Timing (ms)
#define SERIAL_BAUD     9600
#define SCAN_COOLDOWN_MS 1000
#define FEEDBACK_MS     500
#define IDLE_TIMEOUT_MS 3000

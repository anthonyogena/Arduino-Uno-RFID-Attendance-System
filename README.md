# Arduino-Uno-RFID-Attendance-System

An offline, standalone attendance monitoring system built on the Arduino Uno R1. Students tap RFID cards to log their attendance, which is timestamped via a Real-Time Clock (RTC) and saved directly to a MicroSD card as a CSV file. 

This project demonstrates embedded systems programming, hardware interfacing (SPI & I2C), and strict memory management on resource-constrained microcontrollers.

## ✨ Features
- **RFID Identification:** Reads 13.56MHz MIFARE cards via the RC522 module.
- **Accurate Timekeeping:** DS3231 RTC ensures accurate timestamps even during power loss.
- **Duplicate Prevention:** System prevents the same student from scanning twice in a single day.
- **SD Card Logging:** Saves records directly to `ATT.CSV` on a MicroSD card for easy Excel integration.
- **Interactive Feedback:** 16x2 I2C LCD, Green/Red LEDs, and a buzzer provide immediate visual and audible status updates.
- **Standalone Operation:** Runs completely offline without the need for a laptop or internet connection.

## 🛠️ Hardware Requirements
- 1x Arduino Uno R1 (ATmega328P)
- 1x RC522 RFID Reader Module (with 13.56MHz Cards/Fobs)
- 1x DS3231 RTC Module (with CR2032 battery)
- 1x MicroSD Card Reader Module
- 1x MicroSD Card (4GB - 8GB, formatted to FAT32)
- 1x 16x2 LCD Display with I2C Backpack
- 1x Green LED, 1x Red LED (with 220Ω resistors)
- 1x Active Buzzer
- Jumper wires and breadboard

## 🔌 Pin Map
*Careful attention must be paid to the voltage requirements, especially for the RC522.*

| Component | Pin / Signal | Arduino Uno Pin | Voltage |
| :--- | :--- | :--- | :--- |
| **RC522 RFID** | SDA (CS) | D10 | - |
| | SCK | D13 | - |
| | MOSI | D11 | - |
| | MISO | D12 | - |
| | RST | D9 | - |
| | VCC | **3.3V Pin** | ⚠️ **3.3V ONLY** |
| **MicroSD Module** | CS | D4 | - |
| | SCK | D13 | - |
| | MOSI | D11 | - |
| | MISO | D12 | - |
| | VCC | 5V | 5V |
| **DS3231 RTC** | SDA | A4 | - |
| | SCL | A5 | 5V |
| **LCD (I2C)** | SDA | A4 | - |
| | SCL | A5 | 5V |
| **Indicators** | Green LED | D7 | 5V |
| | Red LED | D8 | 5V |
| | Buzzer | D6 | 5V |

## 📂 Project Structure
The codebase is modularized for readability and maintainability.

```text
RFID_Attendance/
├── RFID_Attendance.ino    # Main orchestrator (setup, loop)
├── config.h               # Pin definitions, timing thresholds
├── StudentRegistry.h      # Student structs & data (Stored in PROGMEM)
├── RfidReader.h/.cpp      # Handles RC522 SPI communication
├── Clock.h/.cpp           # Handles DS3231 I2C timekeeping
├── AttendanceLogger.h/.cpp# Handles SD card writing & duplicate tracking
└── UserFeedback.h/.cpp    # Handles LCD, LEDs, and Buzzer

# IoT-Based Medicine Reminder System

## 1. Project Overview

The IoT-Based Medicine Reminder System is designed to help users remember their scheduled medicines through visual and audio alerts. The system uses an ESP8266 microcontroller, an LCD display, LEDs, a buzzer, and IoT connectivity.

The project is designed to provide reminders at scheduled times and support remote monitoring and emergency notifications.

## 2. Objectives

* Remind users when it is time to take their medicines.
* Provide visual alerts using LEDs.
* Provide audio alerts using a buzzer.
* Display relevant information on an LCD.
* Use internet connectivity for IoT communication.
* Support Telegram notifications for emergency alerts.

## 3. Hardware Components

* ESP8266 development board
* 16×2 I2C LCD
* Four LEDs
* Buzzer
* Emergency push button
* Connecting wires
* Power supply

## 4. Software and Technologies

* Arduino IDE
* Embedded C/C++ using the Arduino framework
* Thinger.io for IoT connectivity
* Telegram Bot API for notifications
* NTPClient for time synchronization
* ESP8266 Wi-Fi connectivity

## 5. Working Principle

1. The ESP8266 connects to a configured Wi-Fi network.
2. The system obtains the current time through an NTP server.
3. Medicine reminder times can be configured through the IoT platform.
4. The controller compares the current time with the configured reminder times.
5. When a reminder is triggered, the corresponding LED and buzzer provide alerts.
6. The LCD displays information to the user.
7. The emergency button is intended to trigger a Telegram notification.

## 6. Repository Structure

* `medicine_reminder.ino` — Main Arduino sketch.
* `thinger_connection_test.ino` — Sketch for testing Thinger.io connectivity.
* `implementation_procedure.md` — Implementation procedure and working explanation.
* `components_and_connections.md` — Hardware components and pin connections.
* `project_status.md` — Project status and verification notes.

## 7. Setup Requirements

1. Install the Arduino IDE.
2. Install the ESP8266 board support package.
3. Install the libraries required by the source code.
4. Configure the Wi-Fi credentials.
5. Configure the Thinger.io device credentials.
6. Configure the Telegram bot and chat details if Telegram notifications are required.
7. Select the correct ESP8266 board and serial port.
8. Verify the wiring and compile the sketch before uploading it.

**Security note:** Do not publish Wi-Fi passwords, Telegram bot tokens, or other private credentials in a public repository. Use placeholders in example code and keep actual credentials private.

## 8. Current Verification Status

The physical device has been reported to operate correctly. However, the Thinger.io connection and Telegram notification functionality have not yet been independently verified.

The source code and hardware configuration should be checked against the actual device before making claims about complete end-to-end functionality.

## 9. Future Improvements

* Add confirmation that a medicine has been taken.
* Implement missed-dose detection and notifications.
* Improve configuration security.
* Add clearer monitoring of device connectivity.
* Test the reminder and notification workflow under different conditions.

## 10. Conclusion

This project demonstrates the use of an ESP8266, embedded programming, time synchronization, and IoT services to build a medicine reminder system. It provides a foundation for further development of connected healthcare assistance.

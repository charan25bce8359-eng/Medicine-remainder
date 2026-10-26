# IoT-Based Medicine Reminder Using ESP8266, Thinger.io and Telegram

## 1. Objective

To develop an IoT-based medicine reminder system that alerts users when scheduled medication times arrive and provides remote monitoring capabilities.

## 2. Hardware Components

* ESP8266 NodeMCU development board
* 16×2 LCD with I2C adapter
* Four LEDs with current-limiting resistors
* Active buzzer
* Push button
* Connecting wires
* USB power supply
* Wi-Fi connection

## 3. Software Requirements

* Arduino IDE
* ESP8266 board package
* Thinger.io platform
* UniversalTelegramBot library
* ArduinoJson library
* LiquidCrystal_I2C library
* NTPClient library

## 4. System Working Principle

The ESP8266 acts as the main controller. It connects to a Wi-Fi network and retrieves the current time from an NTP server.

The system uses the Thinger.io platform to provide cloud resources for configuring medicine reminder times. The LCD displays the medicine reminder, while the corresponding LED and buzzer provide visual and audible alerts.

The push button is configured as an input using the ESP8266's internal pull-up resistor. The source code also includes a Telegram notification function for emergency alerts.

## 5. Implementation Procedure

1. Connect the ESP8266 to the required display, LEDs, buzzer and push button according to the circuit diagram.
2. Install the ESP8266 board package in Arduino IDE.
3. Install the libraries required by the source code.
4. Configure the Wi-Fi, Thinger.io and Telegram credentials securely.
5. Initialize the LCD, GPIO pins and network connections.
6. Synchronize the system clock using the NTP client.
7. Configure Thinger.io resources for medicine reminder hours and minutes.
8. Compare the current time with the configured reminder times.
9. Activate the corresponding LED and buzzer when a scheduled time matches.
10. Display the medicine reminder on the LCD.
11. Use the emergency-button function to send a Telegram message when configured correctly.
12. Test the hardware and cloud functions individually.

## 6. Testing and Verification

The physical device should be tested to confirm that the display, LEDs, buzzer and scheduled reminders operate correctly.

Thinger.io connectivity and Telegram notifications should be tested separately. Successful operation of one feature does not establish that all other features work.

## 7. Conclusion

The project demonstrates an IoT-based approach to medication reminders using an ESP8266, a cloud platform and a notification service. Its functionality depends on correct hardware connections, firmware configuration and network connectivity.

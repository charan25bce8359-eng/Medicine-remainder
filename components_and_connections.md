# Components and Connections

## 1. Components Used

| Component                 | Purpose                                         |
| ------------------------- | ----------------------------------------------- |
| ESP8266 NodeMCU           | Main controller with Wi-Fi connectivity         |
| 16×2 LCD with I2C adapter | Displays medicine reminder messages             |
| Four LEDs                 | Indicate the corresponding medicine compartment |
| Active buzzer             | Provides an audible alert                       |
| Push button               | Provides an emergency-button input              |
| Connecting wires          | Connect the electronic components               |
| USB power supply          | Powers the development board                    |

## 2. Pin Mapping

The following connections are documented in the supplied project documentation. Verify them against the actual hardware before making any wiring changes.

| Component        | ESP8266 Pin | GPIO    | Function                     |
| ---------------- | ----------- | ------- | ---------------------------- |
| LCD SCL          | D1          | GPIO 5  | I2C clock                    |
| LCD SDA          | D2          | GPIO 4  | I2C data                     |
| LED A            | D3          | GPIO 0  | Medicine indicator A         |
| LED B            | D4          | GPIO 2  | Medicine indicator B         |
| LED C            | D5          | GPIO 14 | Medicine indicator C         |
| LED D            | D6          | GPIO 12 | Medicine indicator D         |
| Emergency button | D7          | GPIO 13 | Button input                 |
| Active buzzer    | D8          | GPIO 15 | Audible alert                |
| Common ground    | GND         | GND     | Ground connection            |
| Positive supply  | Vin         | 5V      | Documented supply connection |

## 3. LCD Interface

The LCD uses an I2C adapter to communicate with the ESP8266 using two signal connections:

* SCL: D1
* SDA: D2

The source code initializes a 16×2 LCD with I2C address `0x27`.

## 4. LED Indicators

The source code assigns four LEDs to pins D3, D4, D5 and D6. Each LED represents a medicine compartment.

The LEDs should use suitable current-limiting resistors when required by the circuit design.

## 5. Buzzer

The buzzer is assigned to pin D8 in the source code. It provides an audible indication when the reminder function is triggered.

## 6. Emergency Button

The emergency button is assigned to pin D7 and configured using `INPUT_PULLUP`.

The documented wiring connects the button between D7 and GND. When pressed, the input reads LOW.

## 7. Safety and Verification

This pin mapping is based on the supplied documentation, not an independent inspection of the circuit. Confirm the actual boa


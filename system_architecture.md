# System Architecture: IoT-Based Medicine Reminder

## 1. Overview

The system uses an ESP8266 microcontroller to coordinate medicine reminders, display information, and communicate with IoT and notification services.

## 2. Main Components

| Component             | Responsibility                                                |
| --------------------- | ------------------------------------------------------------- |
| ESP8266               | Main controller for the reminder system                       |
| 16×2 I2C LCD          | Displays information to the user                              |
| Four LEDs             | Provide visual medicine reminders                             |
| Buzzer                | Provides audio alerts                                         |
| Emergency push button | Requests an emergency notification                            |
| Wi-Fi network         | Provides internet connectivity                                |
| NTP server            | Supplies the current time                                     |
| Thinger.io            | Provides IoT device connectivity and scheduling configuration |
| Telegram Bot API      | Delivers configured notifications                             |

## 3. System Workflow

1. The ESP8266 starts and initializes the connected hardware.
2. The controller attempts to connect to the configured Wi-Fi network.
3. The system synchronizes its clock using an NTP server.
4. The controller processes the configured medicine reminder times.
5. When a scheduled reminder is triggered, the corresponding LED and buzzer alert the user.
6. The LCD displays reminder-related information.
7. When the emergency button is pressed, the firmware attempts to send a Telegram notification.
8. Thinger.io supports remote configuration and IoT communication.

## 4. Architecture Diagram

```text
             +----------------------+
             |      NTP Server      |
             |    Time Reference    |
             +----------+-----------+
                        |
                        v
+----------------+  +--------------------+  +----------------+
| Thinger.io     |<->| ESP8266 Controller |<->| Wi-Fi Network |
| IoT Platform   |   |                    |   +-------+--------+
+----------------+  +----+----+----+------+           |
                         |    |    |                  v
                         |    |    |          +----------------+
                         |    |    +--------->| Telegram Bot   |
                         |    |               | Notifications  |
                         |    |               +----------------+
                         |    |
                   +-----+    +------+
                   |                  |
                   v                  v
             +-----------+      +-----------+
             | LCD       |      | LEDs and  |
             | Display   |      | Buzzer    |
             +-----------+      +-----------+
                         ^
                         |
                  +------+------+
                  | Emergency   |
                  | Push Button |
                  +-------------+
```

*Note: This diagram represents the intended architecture. Actual communication and notification behavior must be verified on the physical device.*

## 5. Important Technical Notes

* The firmware uses an NTP client to synchronize the current time.
* The ESP8266 uses Wi-Fi to communicate with configured online services.
* The LCD communicates through the I2C interface.
* LEDs and the buzzer provide local alerts.
* The emergency button is configured as a digital input.
* Actual behavior depends on the firmware, hardware wiring, and service configuration.

## 6. Verification Status

The physical device has been reported to work. Thinger.io connectivity and Telegram delivery have not yet been independently verified.

```

### 🟢 Step 3: Save it
Click **Commit changes** and use this commit message:

`Add system architecture documentation`

One important detail: the diagram describes the intended design, not proof that every online connection works.

---

### 🏆 What's next after this?

We'll create a **viva preparation sheet** covering:
- Why ESP8266 instead of Arduino Uno?
- What is Thinger.io?
- How does NTP work?
- How does the Telegram bot send alerts?
- What happens when Wi-Fi disconnects?
- How does the emergency button work?

You'll be able to explain the project instead of just showing the hardware. 😎
```

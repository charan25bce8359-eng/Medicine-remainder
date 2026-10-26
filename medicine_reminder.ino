#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Wi-Fi configuration
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Thinger.io configuration
#define THINGER_USERNAME "YOUR_THINGER_USERNAME"
#define THINGER_DEVICE_ID "YOUR_DEVICE_ID"
#define THINGER_DEVICE_CREDENTIAL "YOUR_DEVICE_CREDENTIAL"

// Telegram configuration
#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"

// Hardware pins
const int ledPins[4] = {D3, D4, D5, D6};
const int buzzerPin = D8;
const int emergencyBtnPin = D7;

// Library objects
ThingerESP8266 thing(
    THINGER_USERNAME,
    THINGER_DEVICE_ID,
    THINGER_DEVICE_CREDENTIAL
);

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
LiquidCrystal_I2C lcd(0x27, 16, 2);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);

// Medicine schedule variables
int pillHours[4] = {-1, -1, -1, -1};
int pillMinutes[4] = {-1, -1, -1, -1};

String pillNames[4] = {
    "Pill A", "Pill B", "Pill C", "Pill D"
};

bool alertSent[4] = {false, false, false, false};

unsigned long lastBtnPress = 0;
bool isSendingEmergency = false;

void showDefaultMessage();
void triggerReminder(int index);
void sendEmergencyTelegram();

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }

    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);

    pinMode(emergencyBtnPin, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    lcd.print("System Loading");

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWi-Fi connected!");

    // Configure Telegram HTTPS client
    client.setInsecure();
    client.setBufferSizes(512, 512);

    // Start time synchronization
    timeClient.begin();
    timeClient.update();

    // Notify caretaker that the device has started
    bot.sendMessage(
        CHAT_ID,
        "Medicine Reminder is Online.",
        ""
    );

    // Thinger.io medicine schedule resources
    thing["pill1_hr"] << [](pson& in) {
        if (in.is_empty())
            in = pillHours[0];
        else
            pillHours[0] = in;
    };

    thing["pill1_min"] << [](pson& in) {
        if (in.is_empty())
            in = pillMinutes[0];
        else
            pillMinutes[0] = in;
    };

    thing["pill2_hr"] << [](pson& in) {
        if (in.is_empty())
            in = pillHours[1];
        else
            pillHours[1] = in;
    };

    thing["pill2_min"] << [](pson& in) {
        if (in.is_empty())
            in = pillMinutes[1];
        else
            pillMinutes[1] = in;
    };

    thing["pill3_hr"] << [](pson& in) {
        if (in.is_empty())
            in = pillHours[2];
        else
            pillHours[2] = in;
    };

    thing["pill3_min"] << [](pson& in) {
        if (in.is_empty())
            in = pillMinutes[2];
        else
            pillMinutes[2] = in;
    };

    thing["pill4_hr"] << [](pson& in) {
        if (in.is_empty())
            in = pillHours[3];
        else
            pillHours[3] = in;
    };

    thing["pill4_min"] << [](pson& in) {
        if (in.is_empty())
            in = pillMinutes[3];
        else
            pillMinutes[3] = in;
    };

    showDefaultMessage();
}

void loop() {
    if (!isSendingEmergency) {
        thing.handle();
        timeClient.update();

        // Emergency button handling
        if (digitalRead(emergencyBtnPin) == LOW) {
            if (millis() - lastBtnPress > 8000) {
                isSendingEmergency = true;
                sendEmergencyTelegram();
                isSendingEmergency = false;
                lastBtnPress = millis();
            }
        }

        int currentH = timeClient.getHours();
        int currentM = timeClient.getMinutes();

        // Check scheduled medicine times
        for (int i = 0; i < 4; i++) {
            if (pillHours[i] != -1 &&
                pillHours[i] == currentH &&
                pillMinutes[i] == currentM &&
                !alertSent[i]) {

                Serial.printf(
                    "ALERT: Time for %s\n",
                    pillNames[i].c_str()
                );

                triggerReminder(i);
                alertSent[i] = true;
            }

            if (currentM != pillMinutes[i]) {
                alertSent[i] = false;
            }
        }
    }
}

void sendEmergencyTelegram() {
    Serial.println("Sending emergency alert...");

    lcd.clear();
    lcd.print("EMERGENCY!");
    lcd.setCursor(0, 1);
    lcd.print("Sending Alert...");

    delay(500);

    bool success = bot.sendMessage(
        CHAT_ID,
        "EMERGENCY: Medicine Reminder Help Button Pressed!",
        ""
    );

    if (success) {
        Serial.println("Telegram: Message sent");

        lcd.setCursor(0, 1);
        lcd.print("Sent OK!");
    } else {
        Serial.println("Telegram: Send failed");

        lcd.setCursor(0, 1);
        lcd.print("Send Failed");

        if (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
    }

    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);

    delay(3000);
    showDefaultMessage();
}

void triggerReminder(int index) {
    lcd.clear();
    lcd.print("TIME FOR:");
    lcd.setCursor(0, 1);
    lcd.print(pillNames[index]);

    for (int i = 0; i < 10; i++) {
        digitalWrite(ledPins[index], HIGH);
        tone(buzzerPin, 1000);

        delay(300);

        digitalWrite(ledPins[index], LOW);
        noTone(buzzerPin);

        delay(200);
    }

    showDefaultMessage();
}

void showDefaultMessage() {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Medicine");

    lcd.setCursor(0, 1);
    lcd.print("Reminder");
}

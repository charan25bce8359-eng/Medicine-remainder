#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "YOUR_USERNAME"
#define DEVICE_ID "medicine_reminder"
#define DEVICE_CREDENTIAL "YOUR_DEVICE_CREDENTIAL"

#define SSID "YOUR_WIFI_NAME"
#define SSID_PASSWORD "YOUR_WIFI_PASSWORD"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
    Serial.begin(115200);
    thing.add_wifi(SSID, SSID_PASSWORD);

    thing["status"] >> [](pson& out) {
        out = "Medicine Reminder Online";
    };
}

void loop() {
    thing.handle();
}

#include <Arduino.h>
#include "ESP8266WiFi.h"

const char *ssid = "Franxx";
const char *password = "nopenope";

WiFiServer wifiServer(80);

void connectWifi();

void closeClient(WiFiClient &client);

const int ALL_PINS[] = {D0, D1, D2, D3, D4, D5, D6, D7, D8};
// const int ALL_PINS[] = {D3, D4, D5};

static const int READ_PINS = 6;

static const int WRITE_PINS = 8;

void setup() {

    Serial.begin(115200);

    delay(1000);

    connectWifi();

    wifiServer.begin();
}

void connectWifi() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting..");
    }

    Serial.print("Connected to WiFi. IP:");
    Serial.println(WiFi.localIP());

    for (int pin :ALL_PINS) {
        pinMode(pin, OUTPUT);
    }
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) //if we get disconnected from wifi, try to reconnect
        connectWifi();

    WiFiClient client = wifiServer.available();

    if (client) { //has new connected client?
        Serial.println("New client");
        while (client.connected()) {
            delay(200); //wait for client done sending
            while (client.available() > 0) {
                int command = client.read();
                Serial.print("Client command: ");
                Serial.println(command);

                if (command == READ_PINS) {
                    for (int pin : ALL_PINS) { //send all digital pins' status
                        client.write(digitalRead(pin));
                    }
                    client.write(analogRead(A0) * 256 / 1024); //send analog pin value, fit it into one byte
                } else if (command == WRITE_PINS) {
                    int address = client.read(); //address of digital pin from 0-11. analog = 100
                    int value = client.read();
                    Serial.print("Client address: ");
                    Serial.println(address);
                    Serial.print("Client value: ");
                    Serial.println(value);
                    if (address == 100) {
                        analogWrite(A0, value * 1024 / 256);
                    } else {
                        digitalWrite(ALL_PINS[address], value);
                    }
                }
            }
            delay(10);
        }

        closeClient(client);
    }
}

void closeClient(WiFiClient &client) {
    client.stop();
    Serial.println("Client disconnected");
}

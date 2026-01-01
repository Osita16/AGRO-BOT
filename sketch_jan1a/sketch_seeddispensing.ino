/*
 * AgriBot – Seed Dispenser Node
 */

#include <WiFi.h>
#include <PubSubClient.h>

const char* seed_topic = "agribot/seed_cmd";
const int seedMotorPin = 25;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';

  if (strcmp((char*)payload, "ON") == 0) {
    digitalWrite(seedMotorPin, HIGH);
  } else {
    digitalWrite(seedMotorPin, LOW);
  }
}

void setup() {
  pinMode(seedMotorPin, OUTPUT);
  client.setServer("broker.hivemq.com", 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    client.connect("ESP32_Seed_Node");
    client.subscribe(seed_topic);
  }
  client.loop();
}

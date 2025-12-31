/*
 * AgriBot – Soil Moisture Node (ESP32)
 * Responsibility: ONLY sensing + publishing
 */

#include <WiFi.h>
#include <PubSubClient.h>

// ---------- WiFi ----------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------- MQTT ----------
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT Topic
const char* moisture_topic = "agribot/soil_moisture";

// ---------- Hardware ----------
const int sensorPin = 34;

// Calibration
const int dryValue = 3000;
const int wetValue = 1200;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnectMQTT() {
  while (!client.connected()) {
    client.connect("ESP32_Soil_Node");
  }
}

void setup() {
  Serial.begin(9600);
  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnectMQTT();
  client.loop();

  int raw = analogRead(sensorPin);
  int moisture = map(raw, dryValue, wetValue, 0, 100);
  moisture = constrain(moisture, 0, 100);

  char msg[10];
  itoa(moisture, msg, 10);
  client.publish(moisture_topic, msg);

  Serial.print("Soil Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  delay(2000);
}

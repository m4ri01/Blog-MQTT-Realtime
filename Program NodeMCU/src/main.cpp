#include <Arduino.h>
#include <DHT.h>
#include "ESP8266WiFi.h"
#include <PubSubClient.h>

const char* ssid = "Gulo";
const char* password = "12345678";
const char* mqttServer = "192.168.10.1";
const int mqttPort = 1883;
WiFiClient espClient;
PubSubClient client(espClient);


#define DHTPIN 14  
#define DHTTYPE DHT11  

unsigned long interval = 1000;
unsigned long lasttime = millis();
unsigned long now;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
      String client_id = "Tes-Node0";
      if (client.connect(client_id.c_str())) {
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
}

void loop() {
  float t = dht.readTemperature();
  String pesanKirim = "Suhu = "+ (String)t;
  now = millis();
  if(now - lasttime>=interval) {
    lasttime = now;
    Serial.println(pesanKirim);
    client.publish("/data/tes",((String)t).c_str());
  }
  client.loop();
}
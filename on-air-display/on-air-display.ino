#include <WiFi.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include "iot.h"

unsigned long previousMillis = 0;
unsigned long interval = 30000;

WiFiClient net;
MQTTClient client;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int led_color = strip.Color(0, 150, 0);


void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("\nIp: ");
  Serial.println(WiFi.localIP());

}

void initIOT()
{
  client.begin(IOT_ENDPOINT, net);
  Serial.print("Connecting to MQTT: %s ", IOT_ENDPOINT);
  while (!client.connect(THINGNAME, IOT_USER, IOT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("MQTT Timeout!");
    return;
  }

  client.onMessage(onMqttMessage);
  // Subscribe to a topic
  client.subscribe(IOT_SUBSCRIBE_TOPIC);

  Serial.println("MQTT Connected!");
}


void initLed()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void setup() {
  Serial.begin(115200);
  initLed();
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  initIOT();
}



void loop() {
  client.loop();

  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}


void onMqttMessage(String &topic, String &payload) {
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);

  int onair = doc["onair"];
  stateChange(onair);
  Serial.println();
}

void stateChange(int state) {

  char jsonBuffer[512];

  if (state == 1) {
    Serial.println("LED ON");
    strip.clear();
    led_color = strip.Color(250, 255, 255);
    for (int i = 0; i < LED_COUNT; i++) {
      Serial.print("O");
      strip.setPixelColor(i, led_color);
      strip.show();
    }
  }
  else {
    state = 0;
    Serial.println("LED OFF");
    led_color = strip.Color(0, 0, 0);
    strip.clear();
    for (int i = 0; i < LED_COUNT; i++) {
      Serial.print("X");
      strip.setPixelColor(i, led_color);
      strip.show();
    }
  }

}

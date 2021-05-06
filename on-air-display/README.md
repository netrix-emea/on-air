# Edrans On-Air Display

v1 by Jacob Verhoeks &lt;jjverhoeks .. at .. edrans.com>

## Description

Arduino code for an ESP32 that lights a Led strip when a message is received by MQTTClient

1. Connect to Wifi
2. Connect to MQTT Broker server
3. Subscribe to a MQTT topic
4. Loop until message is received
   a  if message is `{ "onair": 1 }` then turn led on
   b. if message is `{ "onair": 0 }` turn the led off


## Usage

* Install the Arduino Software
* Install the ESP32 board software
* Install the required libraries
* Rename the iot.h.templ to iot.h and fill in the required fields
* Run compile and upload to the esp32


### Required Arduino Libraries

| Library           | Author          | Reference                                       |
| ----------------- | --------------- | ----------------------------------------------- |
| MQTT              | Joel Gaelwiler  | <https://github.com/256dpi/arduino-mqtt>        |
| FastLed           | David Garcia    | <https://github.com/FastLED/FastLED>            |
| ArduinoJson       | Benoit Blanchon | <https://arduinojson.org/>                      |
| Adafruit_NeoPixel | Adafruit        | <https://github.com/adafruit/Adafruit_NeoPixel> |

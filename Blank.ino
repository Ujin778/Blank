#include <pgmspace.h>
#include "ESP_MQTT.h"

void setup() {
  ESP_MQTT_setup();

}

void loop() {
  ESP_MQTT_loop();

}

void mqttResubscribeExtra(void) {

}

void mqttCallbackExtra(char* topic, byte* payload, unsigned int length) {

}

String handleRootPageExtra(void) {
  String res = "";

  return res;
}


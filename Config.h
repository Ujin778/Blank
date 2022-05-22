#ifndef __ESPWEBCFG_H
#define __ESPWEBCFG_H
#include <Arduino.h>

//#define _DEBUG

//#define _ESP32

const char _signEEPROM[] PROGMEM = "006";
const char _DeviceVersion[] PROGMEM = "0.001";
const char _DeviceName[] PROGMEM = "TestMod3";

const char WIFISSID[] PROGMEM = "dd-wrt";
const char WIFIPASS[] PROGMEM = "ujin1234";
//const char WIFISSID[] PROGMEM = "Translion";
//const char WIFIPASS[] PROGMEM = "vladimir110279";

const char defPassword[] PROGMEM = "12345678";
const bool def_static = false;
const char def_ip[] = "192.168.0.190";
const char def_gate[] = "192.168.0.1";
const char def_mask[] = "255.255.255.0";
const char def_mqtt_ip[] = "192.168.1.131";
const uint16_t def_mqtt_port = 1883;

#endif

#ifndef __ESPWEBMQTT_H
#define __ESPWEBMQTT_H

#include "Config.h"
#include <EEPROM.h>
#include <DNSServer.h>
#include <PubSubClient.h>

#define _LibraryVersion "0.028"

#ifdef _ESP32
#include <WebServer.h>
#include <WiFi.h>
#include <Update.h>
#else
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#endif

const char pathUpdate[] PROGMEM = "/update"; // Путь до страницы OTA-обновления
const char pathSettings[] PROGMEM = "/settings"; // Путь до страницы конфигурации параметров
const char pathStore[] PROGMEM = "/store"; // Путь до страницы сохранения параметров
const char pathReboot[] PROGMEM = "/reboot"; // Путь до страницы перезагрузки

const char textPlain[] PROGMEM = "text/plain";
const char textHtml[] PROGMEM = "text/html";
const char textJson[] PROGMEM = "text/json";
const char textCss[] PROGMEM = "text/css";
const char applicationJavascript[] PROGMEM = "application/javascript";

const char fileNotFound[] PROGMEM = "FileNotFound";
const char indexHtml[] PROGMEM = "index.html";

const char headerTitleOpen[] PROGMEM = "<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>";
const char headerTitleClose[] PROGMEM = "</title>\n";
const char headerStyleOpen[] PROGMEM = "<style type=\"text/css\">\n";
const char headerStyleClose[] PROGMEM = "</style>\n";
const char headerStyleExtOpen[] PROGMEM = "<link rel=\"stylesheet\" href=\"";
const char headerStyleExtClose[] PROGMEM = "\">\n";
const char headerScriptOpen[] PROGMEM = "<script type=\"text/javascript\">\n";
const char headerScriptClose[] PROGMEM = "</script>\n";
const char headerScriptExtOpen[] PROGMEM = "<script type=\"text/javascript\" src=\"";
const char headerScriptExtClose[] PROGMEM = "\"></script>\n";
const char headerBodyOpen[] PROGMEM = "</head>\n\
<body";
const char footerBodyClose[] PROGMEM = "</body>\n\
</html>";
const char getXmlHttpRequest[] PROGMEM = "function getXmlHttpRequest() {\n\
var xmlhttp;\n\
try {\n\
xmlhttp = new ActiveXObject(\"Msxml2.XMLHTTP\");\n\
} catch (e) {\n\
try {\n\
xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n\
} catch (E) {\n\
xmlhttp = false;\n\
}\n\
}\n\
if ((! xmlhttp) && (typeof XMLHttpRequest != 'undefined')) {\n\
xmlhttp = new XMLHttpRequest();\n\
}\n\
return xmlhttp;\n\
}\n";
const char inputTypeOpen[] PROGMEM = "<input type=\"";
const char inputNameOpen[] PROGMEM = " name=\"";
const char inputValueOpen[] PROGMEM = " value=\"";
const char simpleTagClose[] PROGMEM = " />";
const char typeText[] PROGMEM = "text";
const char typePassword[] PROGMEM = "password";
const char typeRadio[] PROGMEM = "radio";
const char typeCheckbox[] PROGMEM = "checkbox";
const char typeButton[] PROGMEM = "button";
const char typeSubmit[] PROGMEM = "submit";
const char typeReset[] PROGMEM = "reset";
const char typeHidden[] PROGMEM = "hidden";
const char typeFile[] PROGMEM = "file";
const char extraChecked[] PROGMEM = "checked";
const char getElementById[] PROGMEM = "document.getElementById('";

// Имена параметров для Web-форм
const char paramSSID[] PROGMEM = "ssid";
const char paramPassword[] PROGMEM = "password";
const char paramStatic[] PROGMEM = "static";
const char paramIP[] PROGMEM = "IP";
const char paramGate[] PROGMEM = "gate";
const char paramMask[] PROGMEM = "mask";
const char paramReboot[] PROGMEM = "reboot";
const char paramMQTTServer[] PROGMEM = "mqttserver";
const char paramMQTTPort[] PROGMEM = "mqttport";

const uint16_t maxStringLen = 32; // Максимальная длина строковых параметров в Web-интерфейсе

const uint32_t timeout = 300000; // 5 min.

String _ssid;
String _password;
bool _static;
String _ip;
String _gate;
String _mask;
String _mqttServer;
uint16_t _mqttPort;
String _ClientName;
uint32_t _timer1s = 0, _timer100ms = 0, _timer10ms = 0, _uptime = 0;
uint32_t nextTime = timeout;

#ifdef _ESP32
WebServer* _httpServer;
#else
ESP8266WebServer* _httpServer;
#endif

PubSubClient* _pubSubClient;
WiFiClient* _espClient;
DNSServer dnsServer;

void mqttResubscribeExtra(void);
void mqttCallbackExtra(char* topic, byte* payload, unsigned int length);
String handleRootPageExtra(void);
void handleEcoModeExtra(bool val);
void handleIR_RecieveExtra(uint32_t code);
void reboot();
String getBoardId();
void SetPinMode(int8_t PinNbr, uint8_t PinMode);
bool ReadPinState(int8_t PinNbr);
void WritePinState(int8_t PinNbr, bool PinState);
uint8_t readEEPROM(uint16_t offset); // Чтение одного байта из EEPROM
void readEEPROM(uint16_t offset, uint8_t* buf, uint16_t len); // Чтение буфера из EEPROM
void writeEEPROM(uint16_t offset, uint8_t data); // Запись одного байта в EEPROM
void writeEEPROM(uint16_t offset, const uint8_t* buf, uint16_t len); // Запись буфера в EEPROM
uint16_t readEEPROMString(uint16_t offset, String& str, uint16_t maxlen); // Чтение строкового параметра из EEPROM, при успехе возвращает смещение следующего параметра
uint16_t writeEEPROMString(uint16_t offset, const String& str, uint16_t maxlen); // Запись строкового параметра в EEPROM, возвращает смещение следующего параметра
template<typename T> T& getEEPROM(uint16_t offset, T& t) { // Шаблон чтения переменной из EEPROM
  readEEPROM(offset, (uint8_t*)&t, sizeof(T));
  return t;
}
template<typename T> const T& putEEPROM(uint16_t offset, const T& t) { // Шаблон записи переменной в EEPROM
  writeEEPROM(offset, (const uint8_t*)&t, sizeof(T));
  return t;
}
void commitEEPROM(); // Завершает запись в EEPROM
uint8_t crc8EEPROM(uint16_t start, uint16_t end); // Вычисление 8-ми битной контрольной суммы участка EEPROM

uint16_t readConfig(); // Чтение конфигурационных параметров из EEPROM
uint16_t writeConfig(bool commit = true); // Запись конфигурационных параметров в EEPROM
void commitConfig(); // Подтверждение сохранения EEPROM
void defaultConfig(); // Установление параметров в значения по умолчанию
bool setConfigParam(const String& name, const String& value); // Присвоение значений параметрам по их имени

bool setupWiFiAsStation(); // Настройка модуля в режиме инфраструктуры
void setupWiFiAsAP(); // Настройка модуля в режиме точки доступа
void setupWiFi(); // Попытка настройки модуля в заданный параметрами режим, при неудаче принудительный переход в режим точки доступа
void onWiFiConnected(); // Вызывается после активации беспроводной сети

void handleNotFound(); // Обработчик несуществующей страницы
void handleRootPage(); // Обработчик главной страницы
void handleUpdate(); // Обработчик страницы выбора файла для OTA-обновления скетча
void handleSketchUpdated(); // Обработчик страницы окончания OTA-обновления скетча
void handleSketchUpdate(); // Обработчик страницы OTA-обновления скетча
void handleSettings(); // Обработчик страницы настройки параметров
void handleStoreConfig(); // Обработчик страницы сохранения параметров
void handleReboot(); // Обработчик страницы перезагрузки модуля

String btnBack(); // HTML-код кнопки "назад" для интерфейса
String btnSettings(); // HTML-код кнопки настройки параметров
String btnReboot(); // HTML-код кнопки перезагрузки
String btnUpdate(); // HTML-код кнопки OTA-обновления
String navigator(); // HTML-код кнопок интерфейса главной страницы

String webPageStart(const String& title); // HTML-код заголовка Web-страницы
String webPageScript(const String& script, bool file = false); // HTML-код скриптового блока или файла
String webPageBody(); // HTML-код заголовка тела страницы
String webPageEnd(); // HTML-код завершения Web-страницы
String escapeQuote(const String& str); // Экранирование двойных кавычек для строковых значений в Web-формах
String tagInput(const String& type, const String& name, const String& value); // HTML-код для тэга INPUT
String tagInput(const String& type, const String& name, const String& value, const String& extra); // HTML-код для тэга INPUT с дополнительными параметрами

String getUptimeStr(void);

bool mqttReconnect(); // Восстановление соединения с MQTT-брокером
void mqttCallback(char* topic, byte* payload, unsigned int length); // Callback-функция, вызываемая MQTT-брокером при получении топика, на которое оформлена подписка
void mqttResubscribe(); // Осуществление подписки на топики
bool mqttSubscribe(const String& topic); // Хэлпер для подписки на топик
bool mqttPublish(const String& topic, const String& value, bool retain); // Хэлпер для публикации топика
void ESP_MQTT_setup(void);
void ESP_MQTT_loop(void);

String MakeTopicName(String topic) {
  if((topic.charAt(0) == '/') || (topic.length() == 0)) {
    return topic;
  } else {
    return "/" + String(_DeviceName) + "/" + topic;
  }
}

String bool2string(bool val) {
	if(val) {
		return "1";
	} else {
		return "0";
	}
}

void SetPinMode(int8_t PinNbr, uint8_t PinMode) {
  pinMode(PinNbr, PinMode);
}

bool ReadPinState(int8_t PinNbr) {
  return digitalRead(PinNbr);
}

void WritePinState(int8_t PinNbr, bool PinState) {
  digitalWrite(PinNbr, PinState);
}

uint8_t readEEPROM(uint16_t offset) {
  return EEPROM.read(offset);
}

void readEEPROM(uint16_t offset, uint8_t* buf, uint16_t len) {
  while (len--)
    *buf++ = EEPROM.read(offset++);
}

void writeEEPROM(uint16_t offset, uint8_t data) {
  EEPROM.write(offset, data);
}

void writeEEPROM(uint16_t offset, const uint8_t* buf, uint16_t len) {
  while (len--)
    EEPROM.write(offset++, *buf++);
}

uint16_t readEEPROMString(uint16_t offset, String& str, uint16_t maxlen) {
  str = "";
  for (uint16_t i = 0; i < maxlen; ++i) {
    char c = readEEPROM(offset + i);
    if (! c)
      break;
    else
      str += c;
  }

  return offset + maxlen;
}

uint16_t writeEEPROMString(uint16_t offset, const String& str, uint16_t maxlen) {
  int slen = str.length();

  for (uint16_t i = 0; i < maxlen; ++i) {
    if (i < slen)
      writeEEPROM(offset + i, str[i]);
    else
      writeEEPROM(offset + i, 0);
  }

  return offset + maxlen;
}

void commitEEPROM() {
  EEPROM.commit();
}

uint8_t crc8EEPROM(uint16_t start, uint16_t end) {
  uint8_t crc = 0;

  while (start < end) {
    crc ^= readEEPROM(start++);

    for (uint8_t i = 0; i < 8; ++i)
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
  }

  return crc;
}

inline void commitConfig() {
  commitEEPROM();
}

bool setupWiFiAsStation() {
  const uint32_t timeout = 60000; // 1 min.
  uint32_t maxTime = millis() + timeout;
  IPAddress ip, gate, mask;

  if (! _ssid.length()) {
    return false;
  }

  ip.fromString(_ip);
  gate.fromString(_gate);
  mask.fromString(_mask);

  WiFi.mode(WIFI_STA);
  if(_static) {
    WiFi.config(ip, gate, mask);
  }
  WiFi.begin(_ssid.c_str(), _password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if ((int32_t)(millis() - maxTime) >= 0) {
      return false;
    }
  }

  return true;
}

void setupWiFiAsAP() {
  String password = FPSTR(defPassword);
  IPAddress apIP(192, 168, 4, 1);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(_ClientName.c_str(), password.c_str());
  dnsServer.start(53, "*", apIP);
}

void setupWiFi() {
  if (! setupWiFiAsStation())
    setupWiFiAsAP();

  _httpServer->begin();
}

void handleNotFound() {
  _httpServer->send(404, FPSTR(textPlain), FPSTR(fileNotFound));
}

void handleRootPage() {
  String page = webPageStart(FPSTR(_DeviceName));
  char buf[50];
  
  page += webPageBody();
  page += F("Device name: <b>");
  page += FPSTR(_DeviceName);
  page += F("</b><br>Library version: ");
  page += _LibraryVersion;
#ifdef _ESP32
page += F("(ESP32)");
#else
page += F("(ESP8266)");
#endif
  page += F("<br>Device version: ");
  page += FPSTR(_DeviceVersion);
  page += F("<br>Settings version: ");
  page += FPSTR(_signEEPROM);
  page += F("<br><br>");
  page += F("\n\nMQTT broker: ");
  if (_pubSubClient->connected()) {
    page += F("connected");
  } else {
    page += F("not connected");
  }
  page += F("<br>\n");
  page += F("Uptime: ");
  page += getUptimeStr();
  page += F("<br>\n");
  page += handleRootPageExtra();
  page += F("<br>\n");
  page += navigator();
  page += webPageEnd();

  _httpServer->send(200, FPSTR(textHtml), page);
}

void handleUpdate() {
  String page = webPageStart(F("Sketch Update"));
  page += webPageBody();
  page += F("<form method=\"POST\" action=\"\" enctype=\"multipart/form-data\" onsubmit=\"if (document.getElementsByName('update')[0].files.length == 0) { alert('No file to update!'); return false; }\">\n\
Select compiled sketch to upload:<br/>\n");
  page += tagInput(FPSTR(typeFile), F("update"), "");
  page += '\n';
  page += tagInput(FPSTR(typeSubmit), "", F("Update"));
  page += F("\n\
</form>\n");
  page += webPageEnd();

  _httpServer->send(200, FPSTR(textHtml), page);
}

void handleSketchUpdated() {
  static const char updateFailed[] PROGMEM = "Update failed!";
  static const char updateSuccess[] PROGMEM = "<META http-equiv=\"refresh\" content=\"15;URL=\">Update successful! Rebooting...";

  _httpServer->send(200, FPSTR(textHtml), Update.hasError() ? FPSTR(updateFailed) : FPSTR(updateSuccess));

  ESP.restart();
}

void handleSketchUpdate() {
  if (_httpServer->uri() != FPSTR(pathUpdate))
    return;
  HTTPUpload& upload = _httpServer->upload();
  if (upload.status == UPLOAD_FILE_START) {
    uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
    if (! Update.begin(maxSketchSpace)) { // start with max available size
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { // true to set the size to the current progress
    }
  } else if (upload.status == UPLOAD_FILE_ABORTED) {
    Update.end();
  }
  yield();
}

void handleSettings() {
  String script = F("function validateForm(form) {\n\
if (form.");
  script += FPSTR(paramSSID);
  script += F(".value == \"\") {\n\
alert(\"SSID must be set!\");\n\
form.");
  script += FPSTR(paramSSID);
  script += F(".focus();\n\
return false;\n\
}\n\
if (form.");
  script += FPSTR(paramPassword);
  script += F(".value == \"\") {\n\
alert(\"Password must be set!\");\n\
form.");
  script += FPSTR(paramPassword);
  script += F(".focus();\n\
return false;\n\
}\n\
if (form.");
  script += FPSTR(paramIP);
  script += F(".value == \"\") {\n\
alert(\"IP must be set!\");\n\
form.");
  script += FPSTR(paramIP);
  script += F(".focus();\n\
return false;\n\
}\n\
if (form.");
  script += FPSTR(paramGate);
  script += F(".value == \"\") {\n\
alert(\"Gate must be set!\");\n\
form.");
  script += FPSTR(paramGate);
  script += F(".focus();\n\
return false;\n\
}\n\
if (form.");
  script += FPSTR(paramMask);
  script += F(".value == \"\") {\n\
alert(\"Mask must be set!\");\n\
form.");
  script += FPSTR(paramMask);
  script += F(".focus();\n\
return false;\n\
}\n\
return true;\n\
}\n");

  String page = webPageStart(F("Settings"));
  page += webPageScript(script);
  page += webPageBody();
  page += F("<form name=\"settings\" method=\"GET\" action=\"");
  page += FPSTR(pathStore);
  page += F("\" onsubmit=\"return validateForm(this)\">\n\
<h3>WiFi Setup</h3>\n\
<label>SSID:</label><br/>\n");
  page += tagInput(FPSTR(typeText), FPSTR(paramSSID), _ssid, String(F("size=")) + String(maxStringLen) + String(F(" maxlength=")) + String(maxStringLen));
  page += F("\n*<br/>\n\
<label>Password:</label><br/>\n");
  page += tagInput(FPSTR(typePassword), FPSTR(paramPassword), _password, String(F("size=")) + String(maxStringLen) + String(F(" maxlength=")) + String(maxStringLen));
  page += F("\n*<br/>\n<p>\n\
<input type=\"checkbox\" name=\"");
    page += FPSTR(paramStatic);
    page += F("\" value=\"1\" ");
    if (_static)
      page += FPSTR(extraChecked);
    page += F(">Static IP mode</input><br>\
<label>IP:</label><br/>\n");
  page += tagInput(FPSTR(typeText), FPSTR(paramIP), _ip, String(F("size=")) + String(maxStringLen) + String(F(" maxlength=")) + String(maxStringLen));
  page += F("\n*<br/>\n\
<label>Gate:</label><br/>\n");
  page += tagInput(FPSTR(typeText), FPSTR(paramGate), _gate, String(F("size=")) + String(maxStringLen) + String(F(" maxlength=")) + String(maxStringLen));
  page += F("\n*<br/>\n\
<label>Mask:</label><br/>\n");
  page += tagInput(FPSTR(typeText), FPSTR(paramMask), _mask, String(F("size=")) + String(maxStringLen) + String(F(" maxlength=")) + String(maxStringLen));
  page += F("\n*<br/>\n");
  page += F("<h3>MQTT Setup</h3>\n\
<label>Server:</label><br/>\n");
  page += tagInput(FPSTR(typeText), FPSTR(paramMQTTServer), _mqttServer, String(F("size=")) + String(maxStringLen) + String(F(" maxlength=")) + String(maxStringLen));
  page += F("\n(leave blank to ignore MQTT)<br/>\n\
<label>Port:</label><br/>\n");
  page += tagInput(FPSTR(typeText), FPSTR(paramMQTTPort), String(_mqttPort), F("size=5 maxlength=5"));
  page += F("\n<br/>\n");
  page += tagInput(FPSTR(typeSubmit), "", F("Save"));
  page += '\n';
  page += btnBack();
  page += tagInput(FPSTR(typeHidden), FPSTR(paramReboot), "1");
  page += F("\n\
</form>\n");
  page += webPageEnd();

  _httpServer->send(200, FPSTR(textHtml), page);
}

void handleStoreConfig() {
  String argName, argValue;

  for (uint8_t i = 0; i < _httpServer->args(); ++i) {
    argName = _httpServer->argName(i);
    argValue = _httpServer->arg(i);
    setConfigParam(argName, argValue);
  }

  writeConfig();

  String page = webPageStart(F("Store Setup"));
  page += F("<meta http-equiv=\"refresh\" content=\"5;URL=/\">\n");
  page += webPageBody();
  page += F("Configuration stored successfully.\n");
  if (_httpServer->arg(FPSTR(paramReboot)) == "1")
    page += F("<br/>\n\
<i>You must reboot module to apply new configuration!</i>\n");
  page += F("<p>\n\
Wait for 5 sec. or click <a href=\"/\">this</a> to return to main page.\n");
  page += webPageEnd();

  _httpServer->send(200, FPSTR(textHtml), page);
}

void handleReboot() {
  String page = webPageStart(F("Reboot"));
  page += F("<meta http-equiv=\"refresh\" content=\"5;URL=/\">\n");
  page += webPageBody();
  page += F("Rebooting...\n");
  page += webPageEnd();

  _httpServer->send(200, FPSTR(textHtml), page);

  ESP.restart();
}

String btnBack() {
  String result = tagInput(FPSTR(typeButton), "", F("Back"), F("onclick=\"location.href='/'\""));
  result += '\n';

  return result;
}

String btnSettings() {
  String result = tagInput(FPSTR(typeButton), "", F("Settings"), String(F("onclick=\"location.href='")) + String(FPSTR(pathSettings)) + String(F("'\"")));
  result += '\n';

  return result;
}

String btnReboot() {
  String result = tagInput(FPSTR(typeButton), "", F("Reboot!"), String(F("onclick=\"if (confirm('Are you sure to reboot?')) location.href='")) + String(FPSTR(pathReboot)) + String(F("'\"")));
  result += '\n';

  return result;
}

String btnUpdate() {
  String result = tagInput(FPSTR(typeButton), "", F("Update"), String(F("onclick=\"location.href='")) + String(FPSTR(pathUpdate)) + String(F("'\"")));
  result += '\n';

  return result;
}

String webPageStart(const String& title) {
  String result = FPSTR(headerTitleOpen);
  result += title;
  result += FPSTR(headerTitleClose);

  return result;
}

String webPageScript(const String& script, bool file) {
  String result;

  if (file) {
    result = FPSTR(headerScriptExtOpen);
    result += script;
    result += FPSTR(headerScriptExtClose);
  } else {
    result = FPSTR(headerScriptOpen);
    result += script;
    result += FPSTR(headerScriptClose);
  }

  return result;
}

String webPageBody() {
  String result = FPSTR(headerBodyOpen);
  result += '>';
  result += '\n';

  return result;
}

String webPageEnd() {
  String result = FPSTR(footerBodyClose);

  return result;
}

String escapeQuote(const String& str) {
  String result;
  unsigned int start = 0;
  int pos;

  while (start < str.length()) {
    pos = str.indexOf('"', start);
    if (pos != -1) {
      result += str.substring(start, pos) + F("&quot;");
      start = pos + 1;
    } else {
      result += str.substring(start);
      break;
    }
  }

  return result;
}

String tagInput(const String& type, const String& name, const String& value) {
  String result = FPSTR(inputTypeOpen);

  result += type;
  result += '"';
  if (name != "") {
    result += FPSTR(inputNameOpen);
    result += name;
    result += '"';
  }
  if (value != "") {
    result += FPSTR(inputValueOpen);
    result += escapeQuote(value);
    result += '"';
  }
  result += '>';

  return result;
}

String tagInput(const String& type, const String& name, const String& value, const String& extra) {
  String result = FPSTR(inputTypeOpen);

  result += type;
  result += '"';
  if (name != "") {
    result += FPSTR(inputNameOpen);
    result += name;
    result += '"';
  }
  if (value != "") {
    result += FPSTR(inputValueOpen);
    result += escapeQuote(value);
    result += '"';
  }
  result += ' ';
  result += extra;
  result += '>';

  return result;
}

uint16_t readConfig() {
  uint16_t offset = 0;

  for (uint8_t i = 0; i < sizeof(_signEEPROM); ++i) {
    char c = pgm_read_byte(_signEEPROM + i);
    if (readEEPROM(offset++) != c)
      break;
  }
  if (offset < sizeof(_signEEPROM)) {
    defaultConfig();
    return 0;
  }
  offset = readEEPROMString(offset, _ssid, maxStringLen);
  offset = readEEPROMString(offset, _password, maxStringLen);
  getEEPROM(offset, _static);
  offset += sizeof(_static);
  offset = readEEPROMString(offset, _ip, maxStringLen);
  offset = readEEPROMString(offset, _gate, maxStringLen);
  offset = readEEPROMString(offset, _mask, maxStringLen);
  offset = readEEPROMString(offset, _mqttServer, maxStringLen);
  getEEPROM(offset, _mqttPort);
  offset += sizeof(_mqttPort);
  uint8_t crc = crc8EEPROM(0, offset);
  if (readEEPROM(offset++) != crc) {
    defaultConfig();
    return 0;
  }
  return offset;
}

uint16_t writeConfig(bool commit) {
  uint16_t offset = 0;

  for (uint8_t i = 0; i < sizeof(_signEEPROM); ++i) {
    char c = pgm_read_byte(_signEEPROM + i);
    writeEEPROM(offset++, c);
  }
  offset = writeEEPROMString(offset, _ssid, maxStringLen);
  offset = writeEEPROMString(offset, _password, maxStringLen);
  putEEPROM(offset, _static);
  offset += sizeof(_static);
  offset = writeEEPROMString(offset, _ip, maxStringLen);
  offset = writeEEPROMString(offset, _gate, maxStringLen);
  offset = writeEEPROMString(offset, _mask, maxStringLen);
  offset = writeEEPROMString(offset, _mqttServer, maxStringLen);
  putEEPROM(offset, _mqttPort);
  offset += sizeof(_mqttPort);
  uint8_t crc = crc8EEPROM(0, offset);
  writeEEPROM(offset++, crc);
  if (commit)
    commitConfig();

  return offset;
}

void defaultConfig() {
  _ssid = FPSTR(WIFISSID);
  _password = FPSTR(WIFIPASS);
  _static = def_static;
  _ip = FPSTR(def_ip);
  _gate = FPSTR(def_gate);
  _mask = FPSTR(def_mask);
  _mqttServer = FPSTR(def_mqtt_ip);
  _mqttPort = def_mqtt_port;
}

bool setConfigParam(const String& name, const String& value) {
  if (name.equals(FPSTR(paramSSID)))
    _ssid = value;
  else if (name.equals(FPSTR(paramPassword))) {
    _password = value;
    _static = false;
  } else if (name.equals(FPSTR(paramStatic)))
    _static = constrain(value.toInt(), 0, 1);
  else if (name.equals(FPSTR(paramIP)))
    _ip = value;
  else if (name.equals(FPSTR(paramGate)))
    _gate = value;
  else if (name.equals(FPSTR(paramMask)))
    _mask = value;
  else if (name.equals(FPSTR(paramMQTTServer)))
    _mqttServer = value;
  else if (name.equals(FPSTR(paramMQTTPort)))
    _mqttPort = value.toInt();
  else
    return false;

  return true;
}

void setupHttpServer() {
  _httpServer->onNotFound(handleNotFound);
  _httpServer->on("/", HTTP_GET, handleRootPage);
  _httpServer->on(String(String('/') + FPSTR(indexHtml)).c_str(), HTTP_GET, handleRootPage);
  _httpServer->on(String(FPSTR(pathUpdate)).c_str(), HTTP_GET, handleUpdate);
  _httpServer->on(String(FPSTR(pathUpdate)).c_str(), HTTP_POST, handleSketchUpdated, handleSketchUpdate);
  _httpServer->on(String(FPSTR(pathSettings)).c_str(), HTTP_GET, handleSettings);
  _httpServer->on(String(FPSTR(pathStore)).c_str(), HTTP_GET, handleStoreConfig);
  _httpServer->on(String(FPSTR(pathStore)).c_str(), HTTP_POST, handleStoreConfig);
  _httpServer->on(String(FPSTR(pathReboot)).c_str(), HTTP_GET, handleReboot);
}

String navigator() {
  String result = btnSettings();
  result += btnReboot();
  result += btnUpdate();

  return result;
}

bool mqttReconnect() {
  const uint32_t timeout = 30000;
  static uint32_t nextTime;
  bool result = false;

  if ((int32_t)(millis() - nextTime) >= 0) {
    result = _pubSubClient->connect(_ClientName.c_str());
    if (result) {
      mqttResubscribe();
    }
    nextTime = millis() + timeout;
  }

  return result;
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  payload[length] = 0;
  mqttCallbackExtra(topic, payload, length);

  String _mqttTopic;
  
#ifdef _DEBUG
  Serial.print("MQTT_inp:");
  Serial.print(topic);
  Serial.print(",");
  Serial.println((char*)payload);
#endif
}

void mqttResubscribe() {
  mqttResubscribeExtra();
}

bool mqttSubscribe(const String& topic) {
#ifdef _DEBUG
  Serial.print("MQTT_subs:");
  Serial.println(topic);
#endif
  if(topic.length() != 0) {
    return _pubSubClient->subscribe(MakeTopicName(topic).c_str());
  } else {
    return true;
  }
}

bool mqttPublish(const String& topic, const String& value, bool retain) {
#ifdef _DEBUG
  Serial.print("MQTT_pub:");
  Serial.print(topic);
  Serial.print(",");
  Serial.println(value);
#endif
  if(topic.length() != 0) {
    return _pubSubClient->publish(MakeTopicName(topic).c_str(), value.c_str(), retain);
  } else {
    return true;
  }
}

String getUptimeStr(void) {
  String ret;

  ret = String(_uptime / 86400);
  ret += "d ";
  uint32_t tmp = _uptime % 86400;
  ret += String(tmp / 3600);
  ret += "h ";
  tmp = tmp % 3600;
  ret += String(tmp / 60);
  ret += "m ";
  tmp = tmp % 60;
  ret += String(tmp);
  ret += "s ";
  return ret;
}

void ESP_MQTT_setup(void) {
#ifdef _DEBUG
  Serial.begin(115200);
  Serial.println("Start debug.");
#endif
#ifdef _ESP32
  _httpServer = new WebServer(80);
#else
  _httpServer = new ESP8266WebServer(80);
#endif
  EEPROM.begin(4096);

  readConfig();

  _ClientName = "ESP_";
  _ClientName += FPSTR(_DeviceName);
#ifdef _ESP32
  WiFi.setHostname(_ClientName.c_str());
#else
  WiFi.hostname(_ClientName);
#endif
  setupWiFi();
  setupHttpServer();
  _espClient = new WiFiClient();
  _pubSubClient = new PubSubClient(*_espClient);
  if (_mqttServer != "") {
    _pubSubClient->setServer(_mqttServer.c_str(), _mqttPort);
    _pubSubClient->setCallback(mqttCallback);
  }
}

void ESP_MQTT_loop(void){
  if ((WiFi.status() != WL_CONNECTED) && ((WiFi.getMode() == WIFI_STA) || ((int32_t)(millis() - nextTime) >= 0))) {
    setupWiFi();
    nextTime = millis() + timeout;
  }

  _httpServer->handleClient();
  if (_mqttServer != "") {
    if (! _pubSubClient->connected())
      mqttReconnect();
    if (_pubSubClient->connected())
      _pubSubClient->loop();
  }
  
  dnsServer.processNextRequest();
  
  if (millis() >= _timer10ms) {
    _timer10ms = millis() + 10;
  }
  if (millis() >= _timer100ms) {
     _timer100ms = millis() + 100;
  }
  if (millis() >= _timer1s) {
    _timer1s = millis() + 1000;
    _uptime++;
  }

  delay(1); // For WiFi maintenance
}

#endif

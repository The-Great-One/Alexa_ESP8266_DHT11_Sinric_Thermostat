 /*
 Version 5 - Apr 10 2020
*/ 
#include <ir_Coolix.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <StreamString.h>
#include "DHTesp.h"
#ifndef UNIT_TEST
#endif
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>
#define DEBUG_WEBSOCKETS true
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
DHTesp dht;
IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)
#define MyApiKey "SecretKey" // TODO: Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard
#define MySSID "SSID" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "PASS" // TODO: Change to your Wifi network password

#define HEARTBEAT_INTERVAL  500000 // 5 Minutes 
#define TEMPRATURE_INTERVAL 300000 // 3 Minutes 
int currenttemp;
float roomtemp;
float humid;
#define SERVER_URL "iot.sinric.com" //"iot.sinric.com"
#define SERVER_PORT 80 // 80
void setSetTemperatureSettingOnServer(String deviceId, float setPoint, String scale, float ambientTemperature, float ambientHumidity);

uint64_t heartbeatTimestamp = 0;
uint64_t tempratureUpdateTimestamp = 0;
bool isConnected = false;

void turnOn(String deviceId) {
  uint16_t rawData[199] = {4460, 4336,  614, 1568,  612, 486,  610, 1572,  614, 1568,  614, 486,  610, 486,  610, 1568,  612, 488,  610, 488,  610, 1572,  612, 486,  610, 486,  610, 1568,  612, 1568,  612, 486,  610, 1574,  612, 488,  610, 486,  610, 1572,  612, 1568,  612, 1568,  614, 1568,  614, 1568,  614, 1570,  612, 1576,  614, 1568,  612, 486,  610, 486,  610, 486,  610, 486,  608, 486,  608, 488,  608, 1574,  612, 1568,  612, 486,  610, 486,  610, 486,  610, 486,  610, 486,  608, 488,  608, 488,  608, 486,  608, 1572,  612, 1568,  612, 1568,  614, 1568,  612, 1568,  614, 1570,  620, 5172,  4488, 4310,  614, 1568,  614, 486,  610, 1572,  612, 1568,  612, 486,  610, 486,  610, 1568,  612, 488,  608, 488,  610, 1572,  612, 486,  610, 486,  610, 1568,  612, 1568,  612, 486,  610, 1576,  612, 488,  610, 486,  610, 1574,  612, 1568,  612, 1568,  614, 1568,  614, 1568,  614, 1570,  612, 1576,  612, 1570,  614, 484,  610, 486,  610, 486,  608, 486,  608, 488,  608, 488,  608, 1574,  612, 1568,  612, 486,  608, 486,  610, 486,  608, 488,  608, 486,  608, 488,  608, 490,  608, 486,  608, 1572,  612, 1568,  612, 1568,  612, 1568,  612, 1568,  614, 1572,  618};  // COOLIX B23FC0

  if (deviceId == "YourDeviceID") // Device ID of first device
  {  
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. AC ON HEX: 0xB23FC0
    Serial.println("Transmitted");
    delay(2000);
    currenttemp= roomtemp-2;
    Serial.println("Room Temp is: "+currenttemp);
    if(currenttemp<24)
    {
            twentyfive(deviceId);
            Serial.println("Set to 25"); 
            currenttemp=25;
    }
    else
    {
    switch(currenttemp)
       {
        case 20:
            twenty(deviceId);
            Serial.println("Set to 20");
            currenttemp=20; 
            break;
        case 21:
            twentyone(deviceId);
            Serial.println("Set to 21"); 
            currenttemp=21;
            break;
        case 22:
            twentytwo(deviceId);
            Serial.println("Set to 22"); 
            currenttemp=22;
            break;
        case 23:
            twentythree(deviceId);
            Serial.println("Set to 23"); 
            currenttemp=23;
            break;
        case 24:
            twentyfour(deviceId);
            Serial.println("Set to 24"); 
            currenttemp=24;
            break;
        case 25:
            twentyfive(deviceId);
            Serial.println("Set to 25"); 
            currenttemp=25;
            break;
        case 26:
            twentysix(deviceId);
            Serial.println("Set to 26"); 
            currenttemp=26;
            break;
        case 27:
            twentyseven(deviceId);
            Serial.println("Set to 27"); 
            currenttemp=27;
            break;
        case 28:
            twentyeight(deviceId);
            Serial.println("Set to 28");
            currenttemp=28; 
            break;
        case 29:
            twentynine(deviceId);
            Serial.println("Set to 29"); 
            currenttemp=29;
            break;
        case 30:
            thirty(deviceId);
            Serial.println("Set to 30"); 
            currenttemp=30;
            break;
                                                             
       }
    }

  } 
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);    
  }     
}
void turnOff(String deviceId) {
  uint16_t rawData[199] = {4416, 4402,  582, 1600,  582, 516,  580, 1604,  582, 1600,  584, 516,  578, 518,  578, 1600,  582, 518,  580, 518,  580, 1604,  582, 516,  578, 516,  578, 1600,  582, 1598,  582, 516,  580, 1604,  606, 494,  580, 1598,  608, 1574,  608, 1574,  608, 1574,  608, 490,  582, 1602,  608, 1576,  608, 1580,  608, 490,  580, 516,  580, 516,  580, 516,  578, 1600,  606, 492,  580, 518,  580, 1604,  608, 1574,  606, 1574,  608, 492,  580, 516,  580, 516,  578, 516,  578, 518,  580, 518,  578, 516,  578, 516,  578, 1602,  604, 1576,  582, 1598,  584, 1598,  582, 1600,  640, 5150,  4410, 4388,  584, 1598,  582, 516,  578, 1604,  584, 1600,  582, 516,  578, 520,  576, 1600,  580, 520,  576, 524,  532, 1648,  580, 518,  532, 562,  534, 1644,  578, 1602,  578, 520,  534, 1650,  536, 566,  532, 1644,  536, 1646,  536, 1644,  536, 1646,  536, 562,  534, 1650,  536, 1648,  536, 1652,  536, 562,  534, 562,  534, 562,  534, 562,  532, 1644,  536, 562,  532, 564,  534, 1650,  534, 1646,  536, 1646,  536, 562,  534, 562,  534, 562,  532, 562,  532, 564,  532, 564,  534, 562,  532, 562,  532, 1648,  534, 1646,  536, 1644,  536, 1646,  536, 1648,  614};  // COOLIX B27BE0
   if (deviceId == "YourDeviceID") // Device ID of first device
   {  
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. AC OFF HEX: 0xB27BE0
     Serial.print("Transmitted");

   }
  else {
     Serial.print("Turn off for unknown device id: ");
     Serial.println(deviceId);    
  }
}
void lowertemp(String deviceId){
  if (deviceId == "YourDeviceID") // Device ID of first device
   {  
       switch(currenttemp)
       {
        case 21:
            twenty(deviceId);
            Serial.println("Set to 20");
            currenttemp=20; 
            break;
        case 22:
            twentyone(deviceId);
            Serial.println("Set to 21"); 
            currenttemp=21;
            break;
        case 23:
            twentytwo(deviceId);
            Serial.println("Set to 22"); 
            currenttemp=22;
            break;
        case 24:
            twentythree(deviceId);
            Serial.println("Set to 23"); 
            currenttemp=23;
            break;
        case 25:
            twentyfour(deviceId);
            Serial.println("Set to 24"); 
            currenttemp=24;
            break;
        case 26:
            twentyfive(deviceId);
            Serial.println("Set to 25"); 
            currenttemp=25;
            break;
        case 27:
            twentysix(deviceId);
            Serial.println("Set to 26"); 
            currenttemp=26;
            break;
        case 28:
            twentyseven(deviceId);
            Serial.println("Set to 27"); 
            currenttemp=27;
            break;
        case 29:
            twentyeight(deviceId);
            Serial.println("Set to 28");
            currenttemp=28; 
            break;
        case 30:
            twentynine(deviceId);
            Serial.println("Set to 29"); 
            currenttemp=29;
            break;                                                 
       }
   }
}
void increasetemp(String deviceId){
  if (deviceId == "YourDeviceID") // Device ID of first device
   {  
       switch(currenttemp)
       {
        case 20:
            twentyone(deviceId);
            Serial.println("Set to 21");
            currenttemp=21; 
            break;
        case 21:
            twentytwo(deviceId);
            Serial.println("Set to 22"); 
            currenttemp=22;
            break;
        case 22:
            twentythree(deviceId);
            Serial.println("Set to 23"); 
            currenttemp=23;
            break;
        case 23:
            twentyfour(deviceId);
            Serial.println("Set to 24"); 
            currenttemp=24;
            break;
        case 24:
            twentyfive(deviceId);
            Serial.println("Set to 25"); 
            currenttemp=25;
            break;
        case 25:
            twentysix(deviceId);
            Serial.println("Set to 26"); 
            currenttemp=26;
            break;
        case 26:
            twentyseven(deviceId);
            Serial.println("Set to 27"); 
            currenttemp=27;
            break;
        case 27:
            twentyeight(deviceId);
            Serial.println("Set to 28"); 
            currenttemp=28;
            break;
        case 28:
            twentynine(deviceId);
            Serial.println("Set to 29");
            currenttemp=29; 
            break;
        case 29:
            thirty(deviceId);
            Serial.println("Set to 30"); 
            currenttemp=30;
            break;
       }
   }
}
void twenty(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4388, 4398,  578, 1606,  576, 520,  576, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  576, 1604,  578, 1604,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  574, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  576, 518,  576, 522,  574, 522,  574, 520,  574, 1610,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  576, 1606,  576, 1606,  576, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  610, 5180,  4434, 4356,  578, 1608,  574, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1608,  576, 522,  576, 518,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  574, 1606,  576, 1606,  574, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 520,  574, 1610,  576, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1608,  574, 1606,  576, 520,  576, 1608,  576, 1606,  576, 1606,  576, 1606,  576, 1610,  610};  // COOLIX B23F20
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=20;
  }
}
void twentyone(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4438, 4354,  578, 1606,  576, 520,  576, 1608,  576, 1606,  576, 522,  574, 520,  576, 1604,  576, 522,  574, 522,  574, 1608,  576, 520,  574, 520,  574, 1604,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  576, 1608,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1606,  576, 1606,  576, 520,  574, 520,  574, 520,  576, 520,  574, 522,  574, 1606,  576, 520,  574, 520,  576, 1604,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  610, 5156,  4438, 4354,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  574, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1604,  576, 1608,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1608,  576, 522,  574, 520,  574, 1604,  576, 1608,  574, 1606,  576, 1606,  576, 1610,  610};  // COOLIX B23F60  
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=21;
  }
}
void twentytwo(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4414, 4398,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 522,  574, 520,  574, 1604,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  576, 1604,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1608,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  576, 520,  574, 520,  574, 520,  576, 522,  574, 522,  574, 1606,  576, 1606,  576, 1606,  576, 520,  574, 520,  574, 520,  576, 522,  574, 1612,  576, 520,  574, 520,  576, 520,  574, 1610,  576, 1606,  576, 1608,  576, 1606,  610, 5182,  4436, 4356,  578, 1606,  576, 520,  574, 1610,  578, 1606,  576, 520,  574, 520,  574, 1606,  574, 522,  574, 522,  574, 1610,  576, 520,  574, 522,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 522,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1606,  576, 1606,  574, 1606,  576, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 520,  574, 520,  574, 520,  576, 1610,  576, 1606,  576, 1606,  576, 1610,  610};  // COOLIX B23F70  
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=22;
  }
}
void twentythree(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4438, 4356,  578, 1606,  576, 520,  574, 1610,  574, 1606,  576, 522,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  574, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  574, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1606,  576, 522,  574, 1610,  576, 520,  574, 520,  574, 520,  574, 522,  574, 1610,  576, 520,  574, 1610,  576, 520,  574, 1610,  576, 1606,  576, 1608,  574, 1606,  610, 5172,  4436, 4356,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  576, 1604,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 524,  574, 520,  576, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  574, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1604,  576, 520,  576, 1610,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 520,  574, 1610,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1610,  610};  // COOLIX B23F50
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=23;
  }
}
void twentyfour(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4448, 4336,  578, 1606,  576, 520,  576, 1610,  576, 1606,  576, 522,  574, 520,  576, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  576, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 524,  574, 520,  574, 1610,  576, 1606,  576, 1606,  578, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 518,  576, 522,  574, 522,  574, 1606,  576, 520,  574, 522,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  610, 5180,  4436, 4356,  578, 1606,  576, 522,  574, 1612,  574, 1608,  574, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 522,  572, 520,  576, 1604,  576, 1608,  576, 520,  574, 1612,  576, 524,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1614,  576, 1606,  576, 520,  576, 520,  574, 520,  574, 520,  574, 520,  574, 522,  576, 522,  574, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 520,  574, 1610,  576, 1606,  576, 1606,  574, 1606,  576, 1606,  574, 1610,  610};  // COOLIX B23F40
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=24;
  }
}
void twentyfive(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4438, 4364,  578, 1606,  576, 520,  574, 1610,  574, 1606,  576, 520,  574, 520,  574, 1606,  576, 524,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  576, 520,  574, 520,  576, 520,  574, 522,  576, 1610,  576, 1606,  576, 520,  574, 520,  576, 518,  574, 520,  574, 520,  574, 522,  574, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  610, 5180,  4436, 4356,  578, 1606,  576, 522,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 522,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  574, 1606,  576, 1606,  576, 1606,  574, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1608,  576, 1606,  576, 1610,  610};  // COOLIX B23FC0
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=25;
  }
}
void twentysix(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4416, 4400,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  576, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 524,  574, 520,  576, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1614,  576, 1606,  576, 520,  574, 520,  576, 518,  576, 520,  574, 520,  576, 522,  574, 1612,  576, 1606,  576, 520,  574, 1610,  576, 520,  574, 520,  574, 520,  574, 522,  576, 522,  574, 520,  574, 1610,  576, 522,  574, 1610,  576, 1606,  576, 1606,  576, 1608,  610, 5174,  4436, 4358,  578, 1608,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1604,  576, 1608,  574, 1614,  574, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1610,  576, 1606,  576, 520,  574, 1610,  576, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 520,  574, 1610,  576, 520,  574, 1610,  574, 1606,  574, 1606,  576, 1610,  610};  // COOLIX B23FD0
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=26;
  }
}
void twentyseven(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4474, 4336,  578, 1606,  576, 520,  574, 1610,  576, 1606,  574, 522,  574, 522,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  576, 1608,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 518,  576, 520,  574, 520,  576, 520,  574, 1612,  574, 520,  574, 520,  574, 1606,  576, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1606,  574, 1606,  576, 520,  576, 1608,  576, 1606,  574, 1606,  576, 1608,  610, 5180,  4434, 4356,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1604,  576, 522,  576, 522,  574, 1608,  576, 520,  576, 520,  574, 1604,  576, 1606,  576, 520,  574, 1612,  574, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1610,  574, 1612,  576, 1606,  574, 520,  574, 520,  574, 520,  576, 520,  574, 520,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1604,  576, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1604,  576, 1606,  576, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1608,  610};  // COOLIX B23F90
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=27;
  }
}
void twentyeight(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4414, 4398,  578, 1606,  574, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1608,  576, 520,  574, 520,  574, 1604,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  574, 1606,  576, 1606,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 518,  574, 520,  574, 520,  576, 522,  574, 1610,  576, 520,  574, 522,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1610,  574, 1606,  576, 1606,  574, 1606,  576, 1606,  576, 1604,  576, 1608,  610, 5180,  4436, 4356,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1604,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  574, 1608,  574, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  574, 1606,  576, 1606,  574, 1608,  576, 1612,  574, 1606,  576, 520,  574, 520,  574, 520,  576, 518,  574, 520,  574, 522,  574, 1612,  576, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 520,  574, 522,  574, 522,  574, 1610,  574, 1606,  576, 1606,  574, 1608,  576, 1606,  576, 1608,  574, 1610,  610};  // COOLIX B23F80
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=28;
  }
}
void twentynine(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4438, 4368,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  576, 522,  576, 1610,  574, 520,  574, 520,  574, 1604,  576, 1606,  576, 520,  576, 1610,  576, 524,  574, 520,  576, 1610,  576, 1606,  576, 1608,  574, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  576, 1612,  576, 520,  574, 1610,  576, 522,  574, 520,  574, 520,  574, 520,  576, 522,  576, 522,  574, 1610,  576, 520,  574, 1610,  574, 1606,  576, 1606,  576, 1606,  576, 1606,  610, 5172,  4436, 4356,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 524,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 522,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 520,  574, 1610,  576, 520,  574, 522,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1610,  576, 522,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1610,  610};  // COOLIX B23FA0
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=29;
  }
}
void thirty(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4388, 4398,  578, 1606,  576, 520,  574, 1610,  576, 1606,  576, 522,  574, 522,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 520,  576, 520,  574, 1604,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  576, 1606,  576, 1606,  576, 1606,  576, 1606,  576, 1608,  576, 1612,  576, 1606,  576, 520,  574, 520,  574, 520,  576, 520,  574, 520,  574, 522,  574, 1612,  576, 522,  574, 1610,  576, 1606,  576, 522,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1606,  576, 520,  574, 520,  576, 1604,  576, 1606,  576, 1606,  576, 1608,  610, 5182,  4438, 4356,  578, 1608,  574, 520,  574, 1610,  576, 1608,  576, 520,  574, 520,  574, 1606,  576, 522,  574, 522,  574, 1610,  576, 522,  574, 520,  574, 1606,  576, 1606,  576, 520,  574, 1612,  576, 522,  574, 520,  574, 1610,  574, 1608,  576, 1606,  576, 1606,  576, 1608,  574, 1608,  576, 1612,  576, 1606,  574, 522,  574, 520,  574, 520,  574, 520,  574, 520,  574, 522,  574, 1612,  576, 522,  572, 1610,  576, 1606,  576, 520,  574, 520,  574, 520,  574, 522,  574, 522,  574, 1606,  576, 520,  574, 520,  576, 1604,  576, 1606,  576, 1608,  574, 1610,  610};  // COOLIX B23FB0
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");
  currenttemp=30;
  }
}
void cool(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4436, 4366,  576, 1608,  574, 522,  572, 1612,  574, 1608,  574, 522,  572, 522,  574, 1606,  574, 524,  574, 524,  572, 1610,  574, 522,  572, 522,  572, 1608,  574, 1608,  574, 522,  572, 1614,  574, 524,  572, 522,  572, 1612,  574, 1608,  574, 1608,  574, 1608,  574, 1608,  574, 1610,  574, 1614,  574, 1608,  574, 522,  572, 522,  572, 522,  572, 522,  572, 522,  572, 522,  574, 1612,  574, 1608,  574, 522,  572, 522,  574, 522,  572, 522,  572, 522,  574, 522,  574, 524,  574, 520,  574, 1610,  574, 1608,  574, 1608,  574, 1608,  574, 1608,  574, 1608,  608, 5182,  4432, 4358,  576, 1608,  574, 522,  572, 1612,  574, 1608,  574, 522,  572, 522,  572, 1608,  572, 524,  572, 524,  574, 1612,  574, 522,  572, 522,  572, 1608,  574, 1608,  574, 522,  572, 1614,  572, 524,  572, 522,  572, 1612,  572, 1608,  574, 1608,  574, 1608,  574, 1608,  574, 1610,  572, 1614,  574, 1608,  574, 524,  572, 522,  572, 522,  572, 522,  572, 522,  572, 524,  572, 1614,  572, 1610,  574, 522,  572, 522,  572, 522,  574, 520,  574, 520,  574, 524,  572, 524,  574, 522,  572, 1612,  572, 1608,  574, 1608,  574, 1606,  574, 1608,  574, 1610,  606};  // COOLIX B23FC0
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");

  }
}
void dry(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4436, 4366,  574, 1610,  572, 522,  574, 1612,  574, 1608,  574, 524,  572, 522,  572, 1608,  572, 526,  572, 524,  572, 1612,  574, 522,  572, 522,  574, 1608,  572, 1610,  574, 522,  572, 1614,  572, 526,  572, 522,  572, 522,  572, 1608,  572, 1608,  574, 1608,  572, 1610,  572, 1610,  572, 1616,  572, 1608,  574, 1608,  574, 522,  572, 522,  572, 522,  572, 522,  572, 524,  572, 1610,  572, 1608,  574, 522,  572, 522,  572, 522,  572, 1612,  572, 522,  572, 526,  572, 524,  572, 522,  572, 1612,  572, 1608,  572, 1608,  574, 522,  572, 1612,  572, 1610,  608, 5184,  4432, 4360,  574, 1610,  574, 522,  572, 1614,  572, 1610,  572, 524,  572, 522,  572, 1608,  572, 526,  570, 526,  572, 1612,  574, 524,  570, 524,  572, 1608,  574, 1610,  572, 524,  572, 1614,  574, 524,  572, 524,  572, 522,  572, 1608,  572, 1608,  574, 1610,  572, 1610,  572, 1610,  574, 1614,  574, 1608,  574, 1608,  572, 524,  572, 522,  572, 522,  572, 524,  570, 524,  572, 1610,  572, 1610,  572, 524,  572, 522,  572, 522,  572, 1614,  572, 524,  570, 526,  572, 524,  572, 522,  572, 1612,  574, 1608,  572, 1608,  574, 524,  570, 1612,  574, 1610,  608};  // COOLIX B21FC4
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");

  }
}
void autom(String deviceId)
{
  if (deviceId == "YourDeviceID") // Device ID of first device
  {
  uint16_t rawData[199] = {4436, 4368,  574, 1610,  574, 522,  572, 1612,  574, 1608,  574, 522,  572, 522,  572, 1608,  574, 524,  572, 524,  572, 1612,  574, 522,  572, 522,  572, 1608,  574, 1608,  574, 522,  572, 1616,  572, 524,  572, 522,  574, 522,  574, 1608,  574, 1608,  574, 1608,  572, 1608,  574, 1610,  574, 1614,  574, 1608,  574, 1608,  574, 522,  572, 522,  574, 522,  572, 522,  572, 524,  574, 1608,  574, 1608,  574, 522,  574, 522,  572, 1608,  574, 522,  572, 522,  572, 524,  574, 524,  574, 522,  572, 1608,  574, 1608,  574, 522,  572, 1612,  574, 1608,  574, 1608,  608, 5162,  4434, 4360,  576, 1610,  574, 522,  572, 1612,  574, 1610,  574, 522,  572, 522,  574, 1606,  574, 524,  572, 524,  572, 1612,  574, 522,  572, 522,  572, 1608,  574, 1610,  574, 522,  574, 1614,  574, 524,  572, 522,  572, 522,  572, 1608,  574, 1608,  576, 1608,  574, 1608,  574, 1610,  574, 1614,  574, 1608,  574, 1608,  574, 522,  572, 522,  572, 522,  574, 522,  572, 524,  572, 1610,  574, 1608,  574, 522,  572, 522,  574, 1608,  574, 522,  572, 522,  572, 524,  572, 524,  574, 522,  572, 1608,  572, 1608,  574, 522,  574, 1612,  574, 1610,  572, 1612,  606};  // COOLIX B21FC8
  irsend.sendRaw(rawData, 199, 38);  // Send a raw data capture at 38kHz. 
  Serial.println("Transmitted");

  }
}
void setPowerStateOnServer(String deviceId, String value);
void readTempature();

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
      Serial.printf("Waiting for commands from sinric.com ...\n");        
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
        // Example payloads

        // For Thermostat
        // {"deviceId": xxxx, "action": "setPowerState", value: "ON"} // https://developer.amazon.com/docs/device-apis/alexa-thermostatcontroller.html
        // {"deviceId": xxxx, "action": "SetTargetTemperature", value: "targetSetpoint": { "value": 20.0, "scale": "CELSIUS"}} // https://developer.amazon.com/docs/device-apis/alexa-thermostatcontroller.html#settargettemperature
        // {"deviceId": xxxx, "action": "AdjustTargetTemperature", value: "targetSetpointDelta": { "value": 2.0, "scale": "FAHRENHEIT" }} // https://developer.amazon.com/docs/device-apis/alexa-thermostatcontroller.html#adjusttargettemperature
        // {"deviceId": xxxx, "action": "SetThermostatMode", value: "thermostatMode" : { "value": "COOL" }} // https://developer.amazon.com/docs/device-apis/alexa-thermostatcontroller.html#setthermostatmode
            
#if ARDUINOJSON_VERSION_MAJOR == 5
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
        DynamicJsonDocument json(1024);
        deserializeJson(json, (char*) payload);      
#endif        
        String deviceId = json ["deviceId"];     
        String action = json ["action"];

        /*if (deviceId == "5axxxxxxxxxxxxxxxxxxx") // Device ID of first device
        { 
          // Check device id if you have multiple devices.
        } */ 
        
        if(action == "setPowerState") { // On or Off
          String value = json ["value"];
          Serial.println("[WSc] setPowerState" + value);
          if(value == "ON") {
             readTempature();
                turnOn(deviceId);
            } else {
               readTempature();
                turnOff(deviceId);
            }
        }
        else if(action == "SetTargetTemperature") { 
          // Alexa, set thermostat to 20      
          //String value = json ["value"];
          String value = json["value"]["targetSetpoint"]["value"];
          String scale = json["value"]["targetSetpoint"]["scale"];

          Serial.println("[WSc] SetTargetTemperature value: " + value);
          Serial.println("[WSc] SetTargetTemperature scale: " + scale);
          if(value=="20")
          {
            twenty(deviceId);
            Serial.println("Set to 20");

          }
          else if(value=="21")
          {
            twentyone(deviceId);
            Serial.println("Set to 21");
          }
          else if(value=="22")
          {
            twentytwo(deviceId);
            Serial.println("Set to 22");
          }
          else if(value=="23")
          {
            twentythree(deviceId);
            Serial.println("Set to 23");
          }
          else if(value=="24")
          {
            twentyfour(deviceId);
            Serial.println("Set to 24");
          }
          else if(value=="25")
          {
            twentyfive(deviceId);
            Serial.println("Set to 25");
          }
          else if(value=="26")
          {
            twentysix(deviceId);
            Serial.println("Set to 26");
          }
          else if(value=="27")
          {
            twentyseven(deviceId);
            Serial.println("Set to 27");
          }
          else if(value=="28")
          {
            twentyeight(deviceId);
            Serial.println("Set to 28");
          }
          else if(value=="29")
          {
            twentynine(deviceId);
            Serial.println("Set to 29");
          }
          else if(value=="30")
          {
            thirty(deviceId);
            Serial.println("Set to 30");
          }
          else if(value>="31")             // Check if value is greater than or equal to 31°C. If so then set value to 30°C.
          {
            thirty(deviceId);
            Serial.println("Set to 30");
            setSetTemperatureSettingOnServer("YourDeviceID", 30, "CELSIUS", roomtemp, humid);
          }
          else if(value<="19")             // Check if value is lower than or equal to 19°C. If so then set value to 20°C.
          {
            twenty(deviceId);
            Serial.println("Set to 20");
            setSetTemperatureSettingOnServer("YourDeviceID", 20, "CELSIUS", roomtemp, humid);
          }
        }
        else if(action == "AdjustTargetTemperature") {
          //Alexa, make it warmer in here
          //Alexa, make it cooler in here
          String value = json["value"]["targetSetpointDelta"]["value"];
          String scale = json["value"]["targetSetpointDelta"]["scale"];  

          Serial.println("[WSc] AdjustTargetTemperature value: " + value);
          Serial.println("[WSc] AdjustTargetTemperature scale: " + scale);          
          if(value == "-1")
          {
             lowertemp(deviceId);
             Serial.println("Cooler");
          }
          else if (value== "1")
          {
            increasetemp(deviceId);
            Serial.println("Warmer");
          }
        }
        else if(action == "SetThermostatMode") { 
          //Alexa, set thermostat name to mode
          //Alexa, set thermostat to automatic
          //Alexa, set kitchen to off
          String value = json["value"]["thermostatMode"]["value"];
          Serial.println("[WSc] SetThermostatMode value: " + value);
          if(value== "COOL")
          {
            cool(deviceId);
            Serial.println("Set to COOL");
          }
          else if(value== "HEAT")
          {
            dry(deviceId);
            Serial.println("Set to HEAT");
          }
          else if(value== "AUTO")
          {
            autom(deviceId);
            Serial.println("Set to AUTO");
          }
        }
        else if (action == "test") {
                Serial.println("[WSc] received test command from sinric.com");
            }
        }
    
    break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
    default: break;
  }
}

void setup() {
  Serial.begin(115200);
  irsend.begin();
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(2, OUTPUT);     // Initialize GPIO2 pin as an output
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);  

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW

  }
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  }

  dht.setup(14, DHTesp::DHT11); // Connect DHT sensor to GPIO 4

  // server address, port and URL
  webSocket.begin(SERVER_URL, SERVER_PORT, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
  webSocket.loop();
  
  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }

      // Send the tempature settings to server
      if((now - tempratureUpdateTimestamp) > TEMPRATURE_INTERVAL) {
          tempratureUpdateTimestamp = now;
          readTempature();
      }
  }   
}

// Read tempratre from DHT Sensor

void readTempature() { 
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float temperaturefh = dht.toFahrenheit(temperature);
  roomtemp=dht.getTemperature();
  humid=dht.getHumidity();
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
//eg: setSetTemperatureSettingOnServer("deviceid", Thermostat Temperature, "CELSIUS" or "FAHRENHEIT", 23.0, 45.3)
// setPoint: Indicates the target temperature to set on the termostat.
  setSetTemperatureSettingOnServer("YourDeviceID", currenttemp, "CELSIUS", temperature, humidity);  
  digitalWrite(2, LOW);   // Turn the LED on by making the voltage LOW
  delay(1000);            // Wait for a second   
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);
  
}

// If you are going to use a push button to on/off the switch manually, use this function to update the status on the server
// so it will reflect on Alexa app.
// eg: setPowerStateOnServer("deviceid", "ON")

// Call ONLY If status changed. DO NOT CALL THIS IN loop() and overload the server. 

void setPowerStateOnServer(String deviceId, String value) {
#if ARDUINOJSON_VERSION_MAJOR == 5
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  DynamicJsonDocument root(1024);
#endif        
  root["deviceId"] = deviceId;
  root["action"] = "setPowerState";
  root["value"] = value;
  StreamString databuf;
#if ARDUINOJSON_VERSION_MAJOR == 5
  root.printTo(databuf);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  serializeJson(root, databuf);
#endif  
  
  webSocket.sendTXT(databuf);
}

// Call ONLY If status changed. DO NOT CALL THIS IN loop() and overload the server. 

//eg: setSetTemperatureSettingOnServer("deviceid", 25.0, "CELSIUS" or "FAHRENHEIT", 23.0, 45.3)
// setPoint: Indicates the target temperature to set on the termostat.
void setSetTemperatureSettingOnServer(String deviceId, float setPoint, String scale, float ambientTemperature, float ambientHumidity) {
#if ARDUINOJSON_VERSION_MAJOR == 5
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  DynamicJsonDocument root(1024);
#endif        
  root["action"] = "SetTemperatureSetting";
  root["deviceId"] = deviceId;
  
#if ARDUINOJSON_VERSION_MAJOR == 5
  JsonObject& valueObj = root.createNestedObject("value");
  JsonObject& temperatureSetting = valueObj.createNestedObject("temperatureSetting");
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  JsonObject valueObj = root.createNestedObject("value");
  JsonObject temperatureSetting = valueObj.createNestedObject("temperatureSetting");
#endif
  temperatureSetting["setPoint"] = setPoint;
  temperatureSetting["scale"] = scale;
  temperatureSetting["ambientTemperature"] = ambientTemperature;
  temperatureSetting["ambientHumidity"] = ambientHumidity;
   
  StreamString databuf;
#if ARDUINOJSON_VERSION_MAJOR == 5
  root.printTo(databuf);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  serializeJson(root, databuf);
#endif  
  
  webSocket.sendTXT(databuf);
}
// Call ONLY If status changed. DO NOT CALL THIS IN loop() and overload the server. 

void setThermostatModeOnServer(String deviceId, String thermostatMode) {
#if ARDUINOJSON_VERSION_MAJOR == 5
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  DynamicJsonDocument root(1024);
#endif        
  root["deviceId"] = deviceId;  
  root["action"] = "SetThermostatMode";
  root["value"] = thermostatMode;
  StreamString databuf;
#if ARDUINOJSON_VERSION_MAJOR == 5
  root.printTo(databuf);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  serializeJson(root, databuf);
#endif  
  
  webSocket.sendTXT(databuf);
}

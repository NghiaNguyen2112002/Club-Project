#ifndef __MQTT_SERVER_H__
#define __MQTT_SERVER_H__

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 

#include "global.h"

// adafruit server is used in this library//
#define SERVER_PASS                         "aio_LROo234Xf9DvOnkWG7UVOFXAe3En"
#define SERVER_DOMAIN                       "io.adafruit.com"
#define SERVER_USER                         "nghianguyen2112002"

#define TIME_RECONNECTION_THINGSBOARD     500                     //5000 ms

#define NO_OF_CHANNEL                     1

#define CHANNEL_HUMID                 "nghianguyen2112002/feeds/club-humid"

void SV_Init(void);
void SV_CheckConnection(void);
void SV_SendData(char* channel, int value);


#endif
#ifndef __INC_WIFI_CONNECTION_H__
#define __INC_WIFI_CONNECTION_H__


#include <ESP8266WiFi.h>
#include <espnow.h>

#include "global.h"
#include "MQTT_server.h"

#define WIFI_AP                 "Vietstar coffee 5G"
#define WIFI_PASSWORD           "0909098463"

#define WIFI_GATEWAY_STA        "GATEWAY"
#define WIFI_GATEWAY_PASS       "123456789"

void WF_Init(void);
void WF_CheckConnection(void);


#endif
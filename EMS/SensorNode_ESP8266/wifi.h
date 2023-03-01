#ifndef __INC_WIFI_CONNECTION_H__
#define __INC_WIFI_CONNECTION_H__


#include <ESP8266WiFi.h>
#include <espnow.h>

#include "global.h"

#define WIFI_GATEWAY_STA                  "GATEWAY"
#define WIFI_GATEWAY_PASSWORD             "123456789"


void WF_Init(void);
void WF_CheckConnection(void);
void WF_SendData(uint8_t* address, uint8_t* data, int length);

#endif
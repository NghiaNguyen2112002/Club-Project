#ifndef __GLOBAL_H__
#define __GLOBAL_H__


// #include <ThingsBoard.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <espnow.h>

typedef struct struct_message {
  int sensor_node_id;
  float humi;
  float temp;
} struct_message;

//Initialize myData sending to Gateway
extern struct_message myData;
// Initialize ThingsBoard client
extern WiFiClient espClient;


//MAC Address of node sensor 
extern uint8_t broadcastAddress[];

extern String _uart_received;

#endif
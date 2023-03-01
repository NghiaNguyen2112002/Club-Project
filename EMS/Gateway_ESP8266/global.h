#ifndef __GLOBAL_H__
#define __GLOBAL_H__


// #include <ThingsBoard.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <PubSubClient.h> 
#include <espnow.h>

#define NO_OF_NODE_SENSOR             1



typedef struct struct_message {
  int sensor_node_id;
  float humi;
  float temp;
} struct_message;

//Initialize myData sending to thingsboard
extern struct_message myData;
// Initialize ThingsBoard client
extern WiFiClient espClient;
// Initialize ThingsBoard instance
extern PubSubClient client;

//MAC Address of node sensor 
extern uint8_t broadcastAddress[][6];


#endif
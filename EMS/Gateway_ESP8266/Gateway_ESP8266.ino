#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 

#include "global.h"
#include "timer.h"
#include "wifi.h"
#include "MQTT_server.h"

#define SERIAL_DEBUG_BAUDRATE         9600


void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  WF_Init();
  SV_Init();

  TMR1_Init(50);
  
  TMR1_SetTime_ms(1000); 
}

void loop() {
  // put your main code here, to run repeatedly:

  if(timer1_flag == 1){
    timer1_flag = 0;
    WF_CheckConnection();
    SV_CheckConnection();
    // SV_SendData(CHANNEL_HUMID, 89);
  }
}

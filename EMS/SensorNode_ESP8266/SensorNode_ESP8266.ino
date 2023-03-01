#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <espnow.h>

#include "global.h"
#include "timer.h"
#include "wifi.h"

#define SERIAL_DEBUG_BAUDRATE         9600
#define UART_TX                       D4
#define UART_RX                       D5

SoftwareSerial mySerial(UART_RX,UART_TX);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  mySerial.begin(SERIAL_DEBUG_BAUDRATE);

  WF_Init();
  TMR1_Init(50);
  
  TMR1_SetTime_ms(1000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    _uart_received = Serial.readStringUntil('#');
    Serial.println(_uart_received);
    myData.humi = _uart_received.toInt();
    WF_SendData(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }

  if(timer1_flag == 1){
    timer1_flag = 0;
    WF_CheckConnection();
  }
}

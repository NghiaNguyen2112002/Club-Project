#include "MQTT_server.h"



void on_message(const char* topic, byte* payload, unsigned int length);

void SV_Init(void){
  client.setServer(SERVER_DOMAIN, 1883);
  client.setCallback(on_message);
}

void SV_CheckConnection(void){
    if ( !client.connected() ) {
      Serial.print("Connecting to Server ...");
      if ( client.connect("GATEWAY ESP8266", SERVER_USER, SERVER_PASS) ) {
        Serial.println( "[DONE]" );

        // Subscribing channel
        client.subscribe(CHANNEL_HUMID);
      } 
      else {
        Serial.print( "[FAILED] [ rc = " );
        Serial.print( client.state() );
        Serial.println( " : retrying in 5 seconds]" );

        // Wait 5 seconds before retrying
        delay(5000);
      }
    }

    client.loop();
}

void SV_SendData(char* channel, int value){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  data["value"] = value;

  char payload[256];
  data.printTo(payload, sizeof(payload));
  String strPayload = String(payload);
  Serial.println(strPayload);

  client.publish(channel, strPayload.c_str());
}

// The callback for when a PUBLISH message is received from the server.
void on_message(const char* topic, byte* payload, unsigned int length) {
  Serial.println("On message");
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);
}

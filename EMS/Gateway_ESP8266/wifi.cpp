#include "wifi.h"

// the Wifi radio's status
int status = WL_IDLE_STATUS;
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Receive from NODE ID: ");
  Serial.println(myData.sensor_node_id);
  Serial.print("HUMI: ");
  Serial.println(myData.humi);
  Serial.print("TEMP: ");
  Serial.println(myData.temp);
  
  //SEND DATA TO SERVER
  SV_SendData(CHANNEL_HUMID, myData.humi);
  // ========================//
}

void WF_Init(void){
  WiFi.mode(WIFI_AP_STA);

  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  Serial.println("Connected to AP");
  Serial.print("IP sta: "); Serial.println(WiFi.localIP());

  WiFi.softAP(WIFI_GATEWAY_STA, WIFI_GATEWAY_PASS);
  Serial.print("IP ap: "); Serial.println(WiFi.softAPIP());

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

    // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  for(int i = 0; i < NO_OF_NODE_SENSOR; i++){
    esp_now_add_peer(broadcastAddress[i], ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  }

  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}


void Reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}

void WF_CheckConnection(){
  if (WiFi.status() != WL_CONNECTED) {
    Reconnect();
  }
}
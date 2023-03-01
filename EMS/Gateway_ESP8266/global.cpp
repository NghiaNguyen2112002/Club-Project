#include "global.h"

WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);

struct_message myData = {0, 0, 0};

uint8_t broadcastAddress[][6] = {0x48, 0x3F, 0xDA, 0x68, 0x13, 0xC5};



uint16_t _time_reconnection_thingboard = 0;
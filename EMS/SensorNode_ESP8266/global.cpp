#include "global.h"

WiFiClient espClient = WiFiClient();

struct_message myData = {0, 0, 0};

uint8_t broadcastAddress[6] = {0x3C, 0x61, 0x05, 0xD0, 0x8F, 0xD2};


uint16_t _time_reconnection_thingboard = 0;

 String _uart_received = "";
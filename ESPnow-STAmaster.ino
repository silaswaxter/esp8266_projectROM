#include <ESP8266WiFi.h>
extern "C" {              //see https://embeddedartistry.com/blog/2017/4/4/extern-c
  #include <espnow.h>
}

#define WIFI_CHANNEL 1

uint8_t hubMacAdd[] = {0x86, 0x0D, 0x8E, 0x8F, 0x46, 0x76};
uint8_t s1MacAdd[] = {0x84, 0x0D, 0x8E, 0x8A, 0x92, 0xCF};
uint8_t key[16] = {0x71, 0x39, 0x7A, 0x24, 0x43, 0x26, 0x46, 0x29, 0x4A, 0x40, 0x4D, 0x63, 0x51, 0x66, 0x54, 0x6A};

#define w 0
#define x 1
#define y 2
#define z 3
union SENSOR_DATA{
  uint8_t msgBuffer[16];
  float q[4];               //quat[w] = quat[0] bc of define above
} sens;

void setup() {
  Serial.begin(115200);
  Serial.println("\n");
  Serial.println("ESP_Now Master/Sensor\n");
  
  WiFi.mode(WIFI_STA);    //Station mode for esp-now sensor node
  WiFi.disconnect();  
  initEspNowMaster();

  sens.q[w] = 1.234; sens.q[x] = 5.678; sens.q[y] = 9.012; sens.q[z] = 3.456;
  
  Serial.printf("This mac: %s \n", WiFi.macAddress().c_str()); 
  Serial.println("Setup done\n-------------------------------\n\n");
}

void loop() {
  esp_now_send(hubMacAdd, sens.msgBuffer, sizeof(sens.msgBuffer));
  delay(500);
}

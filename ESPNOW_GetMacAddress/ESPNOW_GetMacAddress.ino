#include <ESP8266WiFi.h>
 
void setup()
{
  Serial.begin(115200);
//  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress()); //50:02:91:FC:11:16
}
 
void loop()
{
  Serial.println(WiFi.macAddress());
  delay(5000);
}
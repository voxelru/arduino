#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "2_4G_MegaFon_FR1000-B33B";
const char* password = "36293261";

const int ESP_BUILTIN_LED = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ESP_BUILTIN_LED, OUTPUT);

  WiFi.mode(WIFI_STA);                                                                        
  WiFi.hostname("ESP8266_v3");
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    // Serial.println("Connection Failed! Rebooting...");
    //  "Соединиться не удалось! Перезагрузка..."
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.begin();
}

// the loop function runs over and over again forever
void loop() {
  ArduinoOTA.handle();

  digitalWrite(ESP_BUILTIN_LED, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(ESP_BUILTIN_LED, HIGH);   // turn the LED off by making the voltage LOW
  delay(100);                      // wait for a second
}

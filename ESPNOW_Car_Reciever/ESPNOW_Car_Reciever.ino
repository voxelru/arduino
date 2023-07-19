/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

//my mac E8:DB:84:DE:E6:16

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message
{
  byte xAxisValue;
  byte yAxisValue;
  byte switchPressed;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("X: ");
  Serial.println(myData.xAxisValue);
  Serial.print("Y: ");
  Serial.println(myData.yAxisValue);
  Serial.print("Z: ");
  Serial.println(myData.switchPressed);
  Serial.println();
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("Success initializing ESP-NOW");
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  
  if (esp_now_set_self_role(ESP_NOW_ROLE_SLAVE) != 0) {
    Serial.println("Error initializing ESP-NOW as SLAVE");
    return;
  } else {
    Serial.println("Success initializing ESP-NOW as SLAVE");
  }

  if (esp_now_register_recv_cb(OnDataRecv)) {
    Serial.println("Error registering callback");
    return;
  } else {
    Serial.println("Success registering callback");
  }

  pinMode(5, OUTPUT); // motor A скорость
  pinMode(4, OUTPUT); // motor B скорость
  pinMode(0, OUTPUT); //  motor A направление
  pinMode(2, OUTPUT); //  motor B направление

  myData.xAxisValue = 0;
  myData.yAxisValue = 0;
  myData.switchPressed = 0;
}


// останов
void stop(void) {     
   analogWrite(5, 0);     
     analogWrite(4, 0); 
}  
// вперед 
void forward(void) {
     analogWrite(5, 1023); analogWrite(4, 1023);
     digitalWrite(0, HIGH);digitalWrite(2, HIGH); 
}  
// назад 
void backward(void) {
     analogWrite(5, 1023);analogWrite(4, 1023);
     digitalWrite(0, LOW);digitalWrite(2, LOW); 
}   
// влево
void left(void) {
     analogWrite(5, 1023);analogWrite(4, 1023);
     digitalWrite(0, LOW);digitalWrite(2, HIGH);
}   
// вправо
void right(void) {
     analogWrite(5, 1023);analogWrite(4, 1023);
     digitalWrite(0, HIGH); digitalWrite(2, LOW); 
}   


void loop() {
  int direction;

  if (myData.xAxisValue == 255 && myData.yAxisValue == 0) {direction=3;}
  else if (myData.xAxisValue == 1 && myData.yAxisValue == 0) {direction=4;}
  else if (myData.xAxisValue == 0 && myData.yAxisValue == 1) {direction=1;}
  else if (myData.xAxisValue == 0 && myData.yAxisValue == 255) {direction=2;}
  else if (myData.xAxisValue == 0 && myData.yAxisValue == 0) {direction=5;}

  // выбор для кнопок         
  switch (direction) {
    case 1:  left();
      break;             
    case 2:  right();
      break;
    case 3:  forward();
      break;
    case 4:  backward();
      break;             
    case 5:  stop(); 
      break; 
  }
}

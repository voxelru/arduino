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


#define MOTOR_SPD_L 5
#define MOTOR_SPD_R 4
#define MOTOR_DIR_L 0
#define MOTOR_DIR_R 2

//my mac E8:DB:84:DE:E6:16

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message
{
  int xAxisValue;
  int yAxisValue;
  byte switchPressed;
} struct_message;

// Create a struct_message called myData
struct_message myData;


// останов
void stop(void) {     
   analogWrite(MOTOR_SPD_L, 0);     
     analogWrite(4, 0); 
}  
// вперед 
void forward(void) {
     analogWrite(MOTOR_SPD_L, 150); analogWrite(MOTOR_SPD_R, 150);
     digitalWrite(MOTOR_DIR_L, HIGH);digitalWrite(MOTOR_DIR_R, HIGH); 
}  
// назад 
void backward(void) {
     analogWrite(MOTOR_SPD_L, 150);analogWrite(MOTOR_SPD_R, 150);
     digitalWrite(MOTOR_DIR_L, LOW);digitalWrite(MOTOR_DIR_R, LOW); 
}   
// влево
void left(void) {
     analogWrite(MOTOR_SPD_L, 400);analogWrite(MOTOR_SPD_R, 1000);
     digitalWrite(MOTOR_DIR_L, LOW);digitalWrite(MOTOR_DIR_R, HIGH);
}   
// вправо
void right(void) {
     analogWrite(MOTOR_SPD_L, 1000);analogWrite(MOTOR_SPD_R, 400);
     digitalWrite(MOTOR_DIR_L, HIGH); digitalWrite(MOTOR_DIR_R, LOW); 
}   

static inline int8_t sgn(int val) {
  if (val <= 0) return LOW;
  else return HIGH;
}

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  int velocity, rotation;

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

  velocity = abs(myData.yAxisValue)*2;
  rotation = myData.xAxisValue/2;
  analogWrite(MOTOR_SPD_L, velocity+rotation);
  digitalWrite(MOTOR_DIR_L, !sgn(myData.yAxisValue));

  analogWrite(MOTOR_SPD_R, velocity-rotation);
  digitalWrite(MOTOR_DIR_R, sgn(myData.yAxisValue)); 
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

  pinMode(MOTOR_SPD_L, OUTPUT); // motor A скорость
  pinMode(MOTOR_SPD_R, OUTPUT); // motor B скорость
  pinMode(MOTOR_DIR_L, OUTPUT); //  motor A направление
  pinMode(MOTOR_DIR_R, OUTPUT); //  motor B направление

  myData.xAxisValue = 0;
  myData.yAxisValue = 0;
  myData.switchPressed = 0;
}


void loop() {
  int direction;

  if (myData.xAxisValue == 255 && myData.yAxisValue == 0) {direction=3;} //left
  else if (myData.xAxisValue == 1 && myData.yAxisValue == 0) {direction=4;} //right
  else if (myData.xAxisValue == 0 && myData.yAxisValue == 1) {direction=1;} //forward
  else if (myData.xAxisValue == 0 && myData.yAxisValue == 255) {direction=2;} //backward
  else if (myData.xAxisValue == 0 && myData.yAxisValue == 0) {direction=5;} //stop

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

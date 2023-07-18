//#include <ESP8266WiFi.h>
//#include <espnow.h>

#define X_AXIS_PIN D5
#define Y_AXIS_PIN D6
#define ANALOG_PIN A0
#define SWITCH_PIN D7


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t receiverMacAddress[] = {0x50,0x02,0x91,0xFC,0x11,0x16};  //50:02:91:FC:11:16

struct PacketData
{
  byte xAxisValue;
  byte yAxisValue;
  byte switchPressed;
};
PacketData data;

//This function is used to map 0-4095 joystick value to 0-254. hence 127 is the center value which we send.
//It also adjust the deadband in joystick.
//Jotstick values range from 0-4095. But its center value is not always 2047. It is little different.
//So we need to add some deadband to center value. in our case 1800-2200. Any value in this deadband range is mapped to center 127.
int mapAndAdjustJoystickDeadBandValues(int value, bool reverse)
{
  if (value >= 2200)
  {
    value = map(value, 2200, 4095, 127, 254);
  }
  else if (value <= 1800)
  {
    value = map(value, 1800, 0, 127, 0);  
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  return value;
}

// callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t ");
  Serial.println(status);
  Serial.println(status == ERR_OK ? "Message sent" : "Message failed");
}


void setup() 
{
  
  Serial.begin(115200);
/*  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ERR_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else
  {
    Serial.println("Succes: Initialized ESP-NOW");
  }

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  // Add peer        
  if (esp_now_add_peer(receiverMacAddress, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0) != ERR_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
  else
  {
    Serial.println("Succes: Added peer");
  } */
  pinMode(SWITCH_PIN, INPUT);   
}

void loop() 
{
//  data.xAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(X_AXIS_PIN), false);
//  data.yAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(Y_AXIS_PIN), false);  
//  data.switchPressed = false; 

  if (digitalRead(SWITCH_PIN) == LOW)
  {
//    data.switchPressed = true;
    Serial.println("Succes: some pressed");
  }

  delay(1000);
/*
  int result = esp_now_send(receiverMacAddress, (uint8_t *) &data, sizeof(data));
  if (result == ERR_OK) 
  {
    Serial.println("Sent with success");
  }
  else 
  {
    Serial.println("Error sending the data");
  }    
  
  if (data.switchPressed == true)
  {
    delay(500);
  }
  else
  {
    delay(50);
  }*/
}

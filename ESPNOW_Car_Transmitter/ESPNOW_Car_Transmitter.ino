#include <ESP8266WiFi.h>
#include <espnow.h>

#define X_AXIS_PIN D5
#define Y_AXIS_PIN D6
#define ANALOG_PIN A0
#define SWITCH_PIN D7


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t receiverMacAddress[] = {0xE8,0xDB,0x84,0xDE,0xE6,0x16};  //E8:DB:84:DE:E6:16

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
//  if (value >= 610)
//  {
  //  value = map(value, 610, 905, 127, 254);
  value = (round((float)value / 900.0 * 2.0))-1.0;
//  }
//  else if (value <= 600)
//  {
//      value = map(value, 18, 600, 0, 127);
//  }
//  else
//  {
//    value = 127;
//  }

  if (reverse)
  {
//    value = 254 - value;
    value = -value;
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


PacketData read_joystick() {
  int x, y, x0, y0, z;
  PacketData data;

  char buffer[100];

  digitalWrite(X_AXIS_PIN, HIGH);
  x0 = analogRead(ANALOG_PIN);
  x = mapAndAdjustJoystickDeadBandValues(x0, true);
  digitalWrite(X_AXIS_PIN, LOW);

  digitalWrite(Y_AXIS_PIN, HIGH);
  y0 = analogRead(ANALOG_PIN);
  y = mapAndAdjustJoystickDeadBandValues(y0, false);
  digitalWrite(Y_AXIS_PIN, LOW);

  z = digitalRead(SWITCH_PIN);

  sprintf (buffer, "x0: %d x: %d\n y0: %d y: %d\n  z: %d\n", x0, x, y0, y, z);
  Serial.print(buffer);

  data.xAxisValue = x;
  data.yAxisValue = y;
  data.switchPressed = !z;

  return data;
}

void setup() 
{
  pinMode(X_AXIS_PIN, OUTPUT);
  pinMode(Y_AXIS_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(X_AXIS_PIN, LOW);
  digitalWrite(X_AXIS_PIN, LOW);
    
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

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
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  // Register peer
  // Add peer        
  if (esp_now_add_peer(receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != ERR_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
  else
  {
    Serial.println("Succes: Added peer");
  }

//  pinMode(SWITCH_PIN, INPUT); 
}


void loop() 
{
    char buffer[100];
    data = read_joystick();

//  if (digitalRead(SWITCH_PIN) == LOW)
//  {
//    data.switchPressed = true;
//    Serial.println("Succes: some pressed");
//  }

//  sprintf (buffer, "x: %d y: %d z: %d\n", data.xAxisValue, data.yAxisValue, data.switchPressed);
//  Serial.print(buffer);

  delay(100);

  int result = esp_now_send(receiverMacAddress, (uint8_t *) &data, sizeof(data));
  if (result == ERR_OK) 
  {
    Serial.println("Sent with success");
  }
  else 
  {
    Serial.println("Error sending the data");
  }
}

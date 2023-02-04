//                     wwwwwwwww    w     

#include <Keyboard.h>
const int buttonPin = 2;  // the number of the pushbutton pin

int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  pinMode(buttonPin, INPUT);
  // put your setup code here, to run once:
  Keyboard.begin();
}

void loop() {
  int choice, action_time;
  uint8_t action;
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    //    Keyboard.press('w');
    choice = random(1, 4);
    if(choice==1){
      action = KEY_RIGHT_ARROW;
      action_time = random(800, 2000);
    }
    if(choice==2){
      action = KEY_LEFT_ARROW;  // 0x20; //space
      action_time = random(800, 2000);
    }
    if(choice==3){
      action = 0x20; //space
      action_time = random(100, 300);
    }
    Keyboard.press(action);
    delay(action_time);
    Keyboard.release(action);
    action = 'w';  //KEY_UP_ARROW;
    action_time = random(5000, 10000);
    Keyboard.press(action);
    delay(action_time);
    Keyboard.release(action);
  }
}

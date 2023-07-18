#include <Keyboard.h>

#define PIN_FORWARD 8
#define PIN_BACKWARD 9
#define PIN_LEFT 11
#define PIN_RIGHT 10

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_FORWARD, INPUT);
  pinMode(PIN_BACKWARD, INPUT);
  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_RIGHT, INPUT);

//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(PIN_FORWARD) == HIGH) {Keyboard.press('w');} else {Keyboard.release('w');}
  if (digitalRead(PIN_BACKWARD) == HIGH) {Keyboard.press('s');} else {Keyboard.release('s');}
  if (digitalRead(PIN_LEFT) == HIGH) {Keyboard.press('a');} else {Keyboard.release('a');}
  if (digitalRead(PIN_RIGHT) == HIGH) {Keyboard.press('d');} else {Keyboard.release('d');}
}

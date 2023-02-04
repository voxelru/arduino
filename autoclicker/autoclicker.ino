#include <Mouse.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2) == HIGH) {
    // put your main code here, to run repeatedly:
    Mouse.press(MOUSE_LEFT);
    delay(1);
    Mouse.release(MOUSE_LEFT);
    delay(1);
  }
}

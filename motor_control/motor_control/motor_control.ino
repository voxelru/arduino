#include <IRremote.h>

#define MOTOR1_IN 2
#define MOTOR1_PWM 3
#define MOTOR2_IN 4
#define MOTOR2_PWM 5

#define CM_FORWARD 24
#define CM_BACKWARD 82
#define CM_LEFT 8
#define CM_RIGHT 90
#define CM_STOP 28

IRrecv irrecv(6);
decode_results results;

int direction = CM_STOP;

void setup() {
  pinMode(MOTOR1_IN, OUTPUT);
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR2_IN, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);

  pinMode(13, OUTPUT);
//  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  int action = CM_STOP;
  if(irrecv.decode()) {
    digitalWrite(13, HIGH);
    action = irrecv.decodedIRData.command;
    if (action == CM_FORWARD or action == CM_BACKWARD or action == CM_STOP) {
      direction = action;
    }

//    Serial.println(irrecv.decodedIRData.command);
    irrecv.resume();
  }

  if (action == CM_RIGHT) {
    digitalWrite(MOTOR1_PWM, HIGH);
    digitalWrite(MOTOR1_IN, LOW);
    digitalWrite(MOTOR2_PWM, LOW);
    digitalWrite(MOTOR2_IN, LOW);
    delay(100);
  }

  if (action == CM_LEFT) {
    digitalWrite(MOTOR1_PWM, LOW);
    digitalWrite(MOTOR1_IN, LOW);
    digitalWrite(MOTOR2_PWM, HIGH);
    digitalWrite(MOTOR2_IN, LOW);
    delay(100);
  }

  if (direction == CM_FORWARD) {
    digitalWrite(MOTOR1_PWM, HIGH);
    digitalWrite(MOTOR1_IN, LOW);
    digitalWrite(MOTOR2_PWM, HIGH);
    digitalWrite(MOTOR2_IN, LOW);
  }

  if (direction == CM_BACKWARD) {
    digitalWrite(MOTOR1_PWM, LOW);
    digitalWrite(MOTOR1_IN, HIGH);
    digitalWrite(MOTOR2_PWM, LOW);
    digitalWrite(MOTOR2_IN, HIGH);
  }

  if (direction == CM_STOP) {
    digitalWrite(MOTOR1_PWM, LOW);
    digitalWrite(MOTOR1_IN, LOW);
    digitalWrite(MOTOR2_PWM, LOW);
    digitalWrite(MOTOR2_IN, LOW);
  }

  digitalWrite(13, LOW);
}

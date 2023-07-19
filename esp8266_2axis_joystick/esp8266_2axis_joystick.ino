int mapAndAdjustJoystickDeadBandValues(int value, bool reverse)
{
  if (value >= 610)
  {
    value = map(value, 610, 905, 127, 255);
  }
  else if (value <= 600)
  {
      value = map(value, 18, 600, 0, 127);
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 255 - value;
  }
  return value;
}

void read_joystick(int read_x, int read_y) {
  int x, y, x0, y0, z;
  char buffer[100];

  digitalWrite(read_x, HIGH);
  x0 = analogRead(A0);
  x = mapAndAdjustJoystickDeadBandValues(x0, true);
  digitalWrite(read_x, LOW);

  digitalWrite(read_y, HIGH);
  y0 = analogRead(A0);
  y = mapAndAdjustJoystickDeadBandValues(y0, false);
  digitalWrite(read_y, LOW);

  z = digitalRead(D7);

  sprintf (buffer, "x0: %d x: %d\n y0: %d y: %d\n  z: %d\n", x0, x, y0, y, z);
  Serial.print(buffer);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, INPUT_PULLUP);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  read_joystick(D5, D6);
//  Serial.print(digitalRead(D7));
  delay(100);
}

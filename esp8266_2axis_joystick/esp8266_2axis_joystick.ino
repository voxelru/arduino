void read_joystick(int read_x, int read_y) {
  int x, y;
  char buffer[100];
  digitalWrite(read_x, HIGH);
  x = analogRead(A0);
  digitalWrite(read_x, LOW);
  digitalWrite(read_y, HIGH);
  y = analogRead(A0);
  digitalWrite(read_y, LOW);

  sprintf (buffer, "x: %d y: %d\n", x, y);
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

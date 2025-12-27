int touch = 7;

void setup() {
  pinMode(touch, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(touch);
  Serial.println(value);
  delay(500);
}

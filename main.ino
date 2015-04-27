int INPUT_PIN = 2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(INPUT_PIN);
  Serial.print("input value: ");
  Serial.println(value);
}

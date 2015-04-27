int INPUT_PIN = 2;

int FAN_INPUT_PULSE = 0;

void setup() {
  Serial.begin(9600);

  pinMode(FAN_INPUT_PULSE, INPUT);
  digitalWrite(FAN_INPUT_PULSE, HIGH);
}

void loop() {
  int value = analogRead(INPUT_PIN);
  Serial.print("input value: ");
  Serial.println(value);

  // determine current RPM of the fan
  unsigned long pulse_duration = pulseIn(FAN_INPUT_PULSE, LOW);
  double frequency = 1000000 / pulse_duration;
  Serial.print("fan RPM:");
  Serial.println(frequency / 2 * 60);

  delay(1000);
}

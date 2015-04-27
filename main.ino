int INPUT_PIN = 2;
int OUTPUT_PIN = 3;
int BUTTON_PIN = 5;

int FAN_INPUT_PULSE = 0;

void setup() {
  Serial.begin(9600);

  pinMode(FAN_INPUT_PULSE, INPUT);
  digitalWrite(FAN_INPUT_PULSE, HIGH);

  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int button = digitalRead(BUTTON_PIN);
  Serial.print("button state: ");
  Serial.println(button);

  int value = analogRead(INPUT_PIN);
  Serial.print("input value: ");
  Serial.println(value);

  // adjust the fan speed based on the input value
  analogWrite(OUTPUT_PIN, value / 4);

  // determine current RPM of the fan
  unsigned long pulse_duration = pulseIn(FAN_INPUT_PULSE, LOW);
  double frequency = 1000000 / pulse_duration;
  Serial.print("fan RPM:");
  Serial.println(frequency / 2 * 60);

  delay(1000);
}

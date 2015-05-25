int INPUT_PIN = 0;
int OUTPUT_PIN = 11; // blue
int BUTTON_PIN = 8; // determines whether to turn the fan on or off
int POWER_PIN = 12;

int FAN_INPUT_PULSE = 10; // green

void setup() {
  Serial.begin(9600);

  pinMode(FAN_INPUT_PULSE, INPUT);
  digitalWrite(FAN_INPUT_PULSE, HIGH);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POWER_PIN, OUTPUT);
}

void loop() {
  int button = digitalRead(BUTTON_PIN);
  Serial.print("button state: ");
  Serial.println(button);

  if (button == 0) {
    digitalWrite(POWER_PIN, LOW);
  } else {
    digitalWrite(POWER_PIN, HIGH);
  }

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

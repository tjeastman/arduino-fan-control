int INPUT_PIN = 0;

int FAN_SWITCH_PIN = 8;
int FAN_SENSE_PIN = 10; // green wire
int FAN_CONTROL_PIN = 11; // blue wire
int FAN_POWER_PIN = 12;

int OUTPUT_FREQUENCY = 1000;

void setup() {
  Serial.begin(9600);

  pinMode(FAN_SENSE_PIN, INPUT);
  digitalWrite(FAN_SENSE_PIN, HIGH);

  pinMode(FAN_SWITCH_PIN, INPUT_PULLUP);
  pinMode(FAN_POWER_PIN, OUTPUT);
}

void loop() {
  int switch_state;
  int value;

  for (int i = 0; i < OUTPUT_FREQUENCY; ++i) {
    // turn power to the fan on or off via a MOSFET
    switch_state = digitalRead(FAN_SWITCH_PIN);
    if (switch_state == LOW) {
      digitalWrite(FAN_POWER_PIN, LOW);
    } else {
      digitalWrite(FAN_POWER_PIN, HIGH);
    }

    value = analogRead(INPUT_PIN);

    // adjust the fan speed based on the input value
    analogWrite(FAN_CONTROL_PIN, value / 4);
  }

  // determine current RPM of the fan
  // duration is in microseconds (1/1,000,000 of a second)
  unsigned long pulse_duration = pulseIn(FAN_SENSE_PIN, LOW);
  double frequency = 1000000 / pulse_duration;

  Serial.print("button state: ");
  Serial.println(switch_state);
  Serial.print("input value: ");
  Serial.println(value);
  Serial.print("fan RPM:");
  Serial.println(frequency / 2 * 60);
}

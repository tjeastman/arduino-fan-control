int INPUT_PIN = 0;
int FAN_CONTROL_PIN = 11; // blue
int FAN_SWITCH_PIN = 8; // determines whether to turn the fan on or off
int POWER_PIN = 12;

int FAN_SENSE_PIN = 10; // green

int OUTPUT_FREQUENCY = 1000;
int iterations = 0;

void setup() {
  Serial.begin(9600);

  pinMode(FAN_SENSE_PIN, INPUT);
  digitalWrite(FAN_SENSE_PIN, HIGH);

  pinMode(FAN_SWITCH_PIN, INPUT_PULLUP);
  pinMode(POWER_PIN, OUTPUT);
}

void loop() {
  iterations++;
  int button = digitalRead(FAN_SWITCH_PIN);

  if (button == 0) {
    digitalWrite(POWER_PIN, LOW);
  } else {
    digitalWrite(POWER_PIN, HIGH);
  }

  int value = analogRead(INPUT_PIN);

  // adjust the fan speed based on the input value
  analogWrite(FAN_CONTROL_PIN, value / 4);

  if (iterations % OUTPUT_FREQUENCY == 0) {
    // determine current RPM of the fan
    // duration is in microseconds (1/1,000,000 of a second)
    unsigned long pulse_duration = pulseIn(FAN_SENSE_PIN, LOW);
    double frequency = 1000000 / pulse_duration;

    Serial.print("button state: ");
    Serial.println(button);
    Serial.print("input value: ");
    Serial.println(value);
    Serial.print("fan RPM:");
    Serial.println(frequency / 2 * 60);
  }
}

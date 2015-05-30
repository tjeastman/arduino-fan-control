int INPUT_PIN = 0;

int FAN_SWITCH_PIN = 8;
int FAN_SENSE_PIN = 10; // green wire
int FAN_CONTROL_PIN = 11; // blue wire
int FAN_POWER_PIN = 12;

int OUTPUT_FREQUENCY = 1000;

void setup()
{
  Serial.begin(9600);

  pinMode(FAN_SENSE_PIN, INPUT);
  digitalWrite(FAN_SENSE_PIN, HIGH);

  pinMode(FAN_SWITCH_PIN, INPUT_PULLUP);
  pinMode(FAN_POWER_PIN, OUTPUT);
}

void setFanPower(boolean power_on)
{
  // turn power to the fan on or off via a MOSFET
  if (power_on) {
    digitalWrite(FAN_POWER_PIN, HIGH);
  } else {
    digitalWrite(FAN_POWER_PIN, LOW);
  }
}

double getFanSpeed()
{
  // determine the current speed of the fan in RPM
  unsigned long pulse_duration = pulseIn(FAN_SENSE_PIN, LOW);
  // duration is in microseconds (1/1,000,000 of a second)
  double frequency = 1000000 / pulse_duration;
  double speed = frequency / 2 * 60;
  return speed;
}

void loop()
{
  int switch_state;
  int potentiometer_value;

  for (int i = 0; i < OUTPUT_FREQUENCY; ++i) {
    switch_state = digitalRead(FAN_SWITCH_PIN);
    setFanPower(switch_state == HIGH);

    potentiometer_value = analogRead(INPUT_PIN);

    // adjust the fan speed based on the input value
    analogWrite(FAN_CONTROL_PIN, potentiometer_value / 4);
  }

  double speed = getFanSpeed();

  Serial.print("switch state: ");
  Serial.println(switch_state);
  Serial.print("potentiometer value: ");
  Serial.println(potentiometer_value);
  Serial.print("fan speed (in RPM):");
  Serial.println(speed);
}

int POT_INPUT_PIN = 0;

int FAN_SWITCH_PIN = 8;
int FAN_SENSE_PIN = 10; // green wire
int FAN_CONTROL_PIN = 11; // blue wire
int FAN_POWER_PIN = 12;

int REPORT_FREQUENCY = 10000;

void setup()
{
  Serial.begin(9600);

  pinMode(FAN_POWER_PIN, OUTPUT);
  pinMode(FAN_SWITCH_PIN, INPUT_PULLUP);
  pinMode(FAN_SENSE_PIN, INPUT);
  digitalWrite(FAN_SENSE_PIN, HIGH);
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
  // the fan signals its speed by pulsing the sense pin high twice per revolution
  unsigned long pulse_duration = pulseIn(FAN_SENSE_PIN, LOW);
  // convert the pulse diration (in microseconds) into Hz
  double frequency = 1000000 / pulse_duration / 2;
  // convert the frequency into RPM
  double speed = frequency * 60;
  return speed;
}

void setFanSpeed(byte duty_cycle)
{
  // set the fan speed based on the PWM duty cycle
  analogWrite(FAN_CONTROL_PIN, duty_cycle);
}

void loop()
{
  int switch_state;
  int potentiometer_value;
  int duty_cycle;

  for (int i = 0; i < REPORT_FREQUENCY; ++i) {
    // read the toggle switch state and enable or disable the fan accordingly
    switch_state = digitalRead(FAN_SWITCH_PIN);
    setFanPower(switch_state == HIGH);

    // read the potentiometer input value in the range [0, 1023] and convert
    // it into an appropriate PWM duty cycle in the range [0, 255]
    potentiometer_value = analogRead(POT_INPUT_PIN);
    duty_cycle = potentiometer_value / 4;
    setFanSpeed(duty_cycle);
  }

  Serial.print("switch state: ");
  Serial.println(switch_state);
  Serial.print("potentiometer value: ");
  Serial.println(potentiometer_value);
  Serial.print("duty cycle: ");
  Serial.println(duty_cycle);
  Serial.print("fan speed (in RPM):");
  if (switch_state == HIGH) {
    double speed = getFanSpeed();
    Serial.println(speed);
  } else {
    Serial.println("OFF");
  }
}

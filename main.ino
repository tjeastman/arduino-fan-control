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

  for (int i = 0; i < OUTPUT_FREQUENCY; ++i) {
    switch_state = digitalRead(FAN_SWITCH_PIN);
    setFanPower(switch_state == HIGH);

    // read the analog input value in the range [0, 1023] and convert
    // it into an appropriate PWM duty cycle in [0, 255]
    potentiometer_value = analogRead(INPUT_PIN);
    duty_cycle = potentiometer_value / 4;
    setFanSpeed(duty_cycle);
  }

  double speed = getFanSpeed();

  Serial.print("switch state: ");
  Serial.println(switch_state);
  Serial.print("potentiometer value: ");
  Serial.println(potentiometer_value);
  Serial.print("duty cycle: ");
  Serial.println(duty_cycle);
  Serial.print("fan speed (in RPM):");
  Serial.println(speed);
}

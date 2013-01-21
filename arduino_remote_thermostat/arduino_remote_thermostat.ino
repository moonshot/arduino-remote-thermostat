int sensor_pin = 5; // TMP36 Vout pin (analog)
int off_switch = 4; // to trigger an OFF signal
int on_switch = 2; // to trigger an ON signal
int too_cold_temp = 65;
int too_hot_temp = 75;
int too_cold_led = 9;
int too_hot_led = 11;
int ok_led = 10;

void setup()
{
  pinMode(off_switch, OUTPUT);
  pinMode(on_switch, OUTPUT);
  pinMode(too_cold_led, OUTPUT);
  pinMode(too_hot_led, OUTPUT);
  pinMode(ok_led, OUTPUT);
  digitalWrite(on_switch, LOW);
  digitalWrite(off_switch, LOW);

  // turn off the heating pad in case it is
  // already on
  digitalWrite(off_switch, HIGH);
  delay(200);
  digitalWrite(off_switch, LOW);
}

void loop()
{
  // get the voltage reading from the temperature sensor
  int reading = analogRead(sensor_pin);

  // convert that reading to degrees Farenheit
  float voltage = reading * 5.0 / 1024.0;
  float degrees_f = (((voltage - 0.5) * 100) * 9.0 / 5.0) + 32.0;

  // if it's too cold, then push the on button
  if (degrees_f < too_cold_temp) {
    // push the on button
    digitalWrite(on_switch, HIGH);
    delay(200);
    digitalWrite(on_switch, LOW);
    digitalWrite(too_cold_led, HIGH);
    digitalWrite(too_hot_led, LOW);
    digitalWrite(ok_led, LOW);
  }

  // if it's too hot, then push the off button
  else if (degrees_f > too_hot_temp) {
    digitalWrite(off_switch, HIGH);
    delay(200);
    digitalWrite(off_switch, LOW);
    digitalWrite(too_cold_led, LOW);
    digitalWrite(too_hot_led, HIGH);
    digitalWrite(ok_led, LOW);
  }

  // temp is just right
  // heating pad can be either on or off
  else {
    digitalWrite(too_cold_led, LOW);
    digitalWrite(too_hot_led, LOW);
    digitalWrite(ok_led, HIGH);
  }

  // wait 60 seconds before the next poll
  delay(60000);
}


void setup_relay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

float get_actual_temperature() {
  float actual_temperature = 0.0;

  // Just get the highest temperature
  for (int i = 0; i < deviceCount; i++) {
    if (temperatures[i] > actual_temperature)
      actual_temperature = temperatures[i];
  }
  return actual_temperature;
}

static long allowed_change_time = 0;
static long relay_next = -1;
static const long relay_interval = 1000;

void loop_relay() {
  long now = millis();
  if (now < relay_next)
    return;
  relay_next = now + relay_interval;

  Serial.println("loop_relay");

  float actual_temperature = get_actual_temperature();

  // Note that the relay control is reversed so
  // - HIGH means off
  // - LOW means on

  int desired_state;
  int actual_state = digitalRead(RELAY_PIN);

  if (actual_temperature > TARGET_TEMPERATURE + TEMPERATURE_TOLERANCE)
    desired_state = HIGH; // OFF


  if (actual_temperature < TARGET_TEMPERATURE - TEMPERATURE_TOLERANCE)
    desired_state = LOW;  // ON


  if (actual_state == desired_state)
    return;

  if (now < allowed_change_time)
    return;

  if (desired_state == HIGH)
    Serial.println("Relay off");
  else
    Serial.println("Relay on");

  digitalWrite(RELAY_PIN, desired_state);

  // Not allowed to change the relay state for the next 30 seconds
  allowed_change_time = now + 30 * 1000;
}



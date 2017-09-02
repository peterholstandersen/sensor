void setup() {

  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  Serial.println("Relay");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  Serial.print(" ");
  Serial.print(__FILE__);
  Serial.print("\n");

  setup_one_wire();
  setup_wifi();
  setup_relay();
}

void loop() {
  loop_one_wire();
  loop_wifi();
  loop_relay();

  // shutdown_wifi();
  // ESP.deepSleep(sleep, RF_CAL);
}

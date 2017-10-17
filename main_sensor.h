#define SLEEP

// const static long sleep = 10 * 1000 * 1000; // 10 sec -- while testing
const static unsigned long sleep = 3600UL * 1000UL * 1000UL;  // 1 hour

void setup()
{
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  Serial.println("Sensor");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  Serial.print(" ");
  Serial.print(__FILE__);
  Serial.print("\n");

  setup_one_wire();
  setup_wifi();

#ifdef SLEEP
  measure_and_sleep();
#endif
}

void measure_and_sleep()
{
  loop_one_wire();
  loop_wifi();

  shutdown_wifi();

  Serial.println("Goodnight");
  Serial.println(millis());
  delay(10);

  ESP.deepSleep(sleep, RF_CAL);
}


void loop()
{
#ifndef SLEEP
  loop_one_wire();
  loop_wifi();
#endif
}


void setup_wifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

long wifi_retry = 0;

// Connect to WiFi if not already connected
bool connect_wifi(bool force) {

  if (WiFi.status() == WL_CONNECTED)
    return true;

  // Not connected: check if it is time try again
  long now = millis();
  if (!force && wifi_retry != 0 && now < wifi_retry) {
    Serial.println("Not time to reconnect yet");
    return false;
  }

  bool led_on = true;
  long timeout = now + 20000;
  while (WiFi.status() != WL_CONNECTED && millis() < timeout) {
    led_on = !led_on;
    digitalWrite(LED_PIN, led_on ?HIGH :LOW);
    digitalWrite(LED_BUILTIN, led_on ?HIGH :LOW);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  else {
    Serial.println("Unable to connect to WiFi");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    wifi_retry = millis() + WIFI_RETRY_DELAY;
    return false;
  }
}

void shutdown_wifi() {
  WiFi.persistent(false);
  WiFi.disconnect();  
}

static const long wifi_interval = WIFI_UPLOAD_INTERVAL;
static long wifi_next;

void loop_wifi() {
  long now = millis();
  if (now < wifi_next)
    return;

  Serial.println("loop_wifi");
  
  wifi_next = now + wifi_interval;

  if (!connect_wifi(false))
    return;
  
  Serial.print("connecting to ");
  Serial.println(host);

  for (int i = 0; i < deviceCount; i++) {
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    digitalWrite(LED_PIN, LOW);
    delay(250);
    digitalWrite(LED_PIN, HIGH);
    
    String url = url_template + "?id=" + deviceId[i] + "&temperature=" + String(temperatures[i], 1);

    Serial.print("Requesting URL: ");
    Serial.println(url);
  
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
		 "Host: " + host + "\r\n" + 
		 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
         Serial.println(">>> Client Timeout !");
	       client.stop();
	       return;
      }
    }

    /*
    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    */
  }
  
  Serial.println("closing connection");
}


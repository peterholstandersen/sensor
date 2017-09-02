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

  bool led_on = true;
  while (WiFi.status() != WL_CONNECTED) {
    led_on = !led_on;
    digitalWrite(LED_PIN, led_on ?HIGH :LOW);
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_PIN, HIGH);

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void shutdown_wifi() {
  WiFi.persistent(false);
  WiFi.disconnect();  
}

static const long wifi_interval = 1000;
static long wifi_next;

void loop_wifi() {
  long now = millis();
  if (now < wifi_next)
    return;

  wifi_next = now + wifi_interval;
  
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


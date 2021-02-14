String lastMachineState;
int lastHxTemperature = NULL;
int lastSteamTemperature = NULL;
long lastTimerStartMillis = 0;
bool lastTimerStarted = false;

void setupWifi() { 
  WiFi.begin(SSID, PSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  client.setServer(MQTT_BROKER, 1883);
}

void updateWifi() {
  if (!client.connected()) {
    while (!client.connected()) {
      client.connect("marax");
      
      delay(100);
    }
  }
  
  client.loop();

  if (lastMachineState != machineState) {
    lastMachineState = machineState;
    broadcastMachineState();   
  }

  if (lastHxTemperature != hxTemperature) {
    lastHxTemperature = hxTemperature;
    broadcastHxTemperature();
  }

  if (lastSteamTemperature != steamTemperature) {
    lastSteamTemperature = steamTemperature;
    broadcastSteamTemperature();
  }

  if (lastTimerStartMillis != timerStartMillis && ((millis() - timerStartMillis ) / 1000) > 15 && timerStarted == false && timerCount > 0) {
    lastTimerStartMillis = timerStartMillis;
    broadcastShot();
  }

  if (lastTimerStarted != timerStarted) {
    lastTimerStarted = timerStarted;
    brodcastPump();
  }
}

void broadcastMachineState() {
  if (machineState == "off") {
    client.publish("/marax/power", "off");
  } else {
    client.publish("/marax/power", "on");
  }
}

void broadcastHxTemperature() {
  client.publish("/marax/hx", String(hxTemperature).c_str());
}

void broadcastSteamTemperature() {
  client.publish("/marax/steam", String(steamTemperature).c_str());
}

void broadcastShot() {
  client.publish("/marax/shot", String(timerCount).c_str());
}

void brodcastPump() {
  if (timerStarted) {
    client.publish("/marax/pump", "on");
  } else {
    client.publish("/marax/power", "off");
  }
}

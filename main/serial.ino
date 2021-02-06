static byte ndx = 0;
char endMarker = '\n';
char rc;

void setupSerial() {
  mySerial.begin(9600);

  pinMode(PUMP_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  memset(receivedChars, 0, numChars);
  mySerial.write(0x11);
}

void updateSerial() {
  while (mySerial.available() ) {
    serialUpdateMillis = millis();
    rc = mySerial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;    
      
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';
      ndx = 0;

      machineState = getMachineState();
      machineHeating = getMachineHeating();
      machineHeatingBoost = getMachineHeatingBoost();
      hxTemperature = getTemperatureHx();
      steamTemperature = getTemperatureSteam();
      Serial.println(receivedChars);
    }
  }
  
  if (millis() - serialUpdateMillis > 5000) {
    serialUpdateMillis = millis();
    memset(receivedChars, 0, numChars);
    Serial.println("Request serial update");
    mySerial.write(0x11);
    machineState = "off";
    machineHeating = NULL;
    machineHeatingBoost = NULL;
    hxTemperature = NULL;
    steamTemperature = NULL;
  }
}

String getMachineState() {
  if (String(receivedChars[0]) == "C") {
    return "C";
  } else if (String(receivedChars[0]) == "V") {
    return "S";
  } else {
    return "X";
  }
}

bool getMachineHeating() {
  return String(receivedChars[23]) == "1";
}

bool getMachineHeatingBoost() {
  return String(receivedChars).substring(18, 22) == "0000";
}

int getTemperatureHx() {
  if (receivedChars[14] && receivedChars[15] && receivedChars[16]) {
    return String(receivedChars).substring(14, 17).toInt();
  }

  return NULL;
}

int getTemperatureSteam() {
  if (receivedChars[6] && receivedChars[7] && receivedChars[8]) {
    return String(receivedChars).substring(6, 9).toInt();
  }

  return NULL;
}

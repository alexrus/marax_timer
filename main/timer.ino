void setupTimer() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void updateTimer() {
  digitalWrite(LED_BUILTIN, digitalRead(PUMP_PIN));
  if (!timerStarted && !digitalRead(PUMP_PIN)) {
    timerStartMillis = millis();
    timerStarted = true;
    Serial.println("Start pump");
  }
  if (timerStarted && digitalRead(PUMP_PIN)) {
    if (timerStopMillis == 0) {
      timerStopMillis = millis();
    }
    if (millis() - timerStopMillis > 500) {
      timerStarted = false;
      timerStopMillis = 0;
//      display.invertDisplay(false);
      Serial.println("Stop pump");
    }
  } else {
    timerStopMillis = 0;
  }
}


String getTimer() {
  char outMin[2];
  if (timerStarted) {
    timerCount = (millis() - timerStartMillis ) / 1000;
    if (timerCount > 15) {
      prevTimerCount = timerCount;
    }
  } else {
    timerCount = prevTimerCount;
  }
  if (timerCount > 99) {
    return "99";
  }
  sprintf( outMin, "%02u", timerCount);
  return outMin;
}

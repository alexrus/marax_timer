void setupDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void render() {
  display.clearDisplay();
  if (machineState != "off") {
    if (timerStarted) {
      renderTimer();
    } else {
      renderDashboard();
    }
  }

  display.display();
}

void renderTimer() {
  display.setTextSize(7);
  display.setCursor(25, 8);
  display.print(getTimer());
}

void renderDashboard() {
  // draw line
  display.drawLine(74, 0, 74, 63, SSD1306_WHITE);
  // draw time seconds
  display.setTextSize(4);
  display.setCursor(display.width() / 2 - 1 + 17, 20);

  display.print(getTimer());

   // draw machine state C/S
  if (machineState) {
    display.setTextSize(2);
    display.setCursor(1, 1);
    display.print(machineState);
   }
    
  // draw heating indicator    
  if (!machineHeatingBoost) {
    if (machineHeating) {
       // draw fill circle if heating on 
       display.fillCircle(45, 7, 6, SSD1306_WHITE);
     } else {
       // draw empty circle if heating off
       display.drawCircle(45, 7, 6, SSD1306_WHITE);
     }
  } else {
    if (machineHeating) {
      // draw fill rectangle if heating on
      display.fillRect(39, 1, 12, 12, SSD1306_WHITE);
    } else {
      // draw empty rectangle if heating off
      display.drawRect(39, 1, 12, 12, SSD1306_WHITE);
    }
  }

  // draw hx temperature
  if (hxTemperature) {
    display.setTextSize(3);
    display.setCursor(1, 20);
    String temp = String(hxTemperature);
    display.print(temp);
    display.print((char)247);
    if (temp.length() < 3) {
      display.print("C");
    }
  }
  
  // draw steam temperature
  if (steamTemperature) {
    display.setTextSize(2);
    display.setCursor(1, 48);
    String temp = String(steamTemperature);
    display.print(temp);
    display.print((char)247);
    display.print("C");
  }
}

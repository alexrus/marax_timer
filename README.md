# marax_timer

***This repository is a rewrite of [espresso_timer](https://github.com/alexrus/espresso_timer) that has better doccumentation and is easyer to use.***

This project was designed to be used with a Lelit MaraX espresso machine, but it works (only the timer functionality) with any espresso machine that has a vibration pump.

**Hardware:**

- NodeMCU (ESP8266)
- 0.96" oled display
- reed sensor
- wires
- 3d printed case ([https://www.thingiverse.com/thing:2937731](https://www.thingiverse.com/thing:2937731))

**Software:**

In order to make NodeMCU working with Arduino IDE follow these instructions: [https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/](https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/)


**Hardware connections:**

You connect the oled display like this:
![](https://circuits4you.com/wp-content/uploads/2019/01/NodeMCU_ESP8266_OLED_Display.png)

The reed switch goes to ground and D7

The reed switch will pe glued onto the machine's vibration pump like this:
![](resources/pump.jpg)

If you have a Lelit MaraX machine, open the underside of the machine and you will see a 6 pin connector.


Connect pin 3 of the machine (RX) to pin D6 (TX) of nodeMCU

Connect pin 4 of the machine (TX) to pin D5 (RX) of nodeMCU

In case this does not work, change the pins connection (pin 3 to D5 & pin 4 to D6)



**Operation:**

When the pump will start, the timer on the screen will also start counting.

When the pump is stopped, the time will remain printed on the screen (if more that 12 seconds have passed) until the next time the pump is activated.

The time is not recorded unless 12 seconds have passed because MaraX machine starts the pump by itself from time to time to fill the boiler with water.

The display should go to sleep after 1 hour, and will wake up when the pump is started.


**UI:**

![](resources/ui.jpg)


This project uses the following dependencies:

* [https://github.com/adafruit/Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [https://github.com/adafruit/Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO)
* [https://github.com/adafruit/Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)



More information about the project and progress [here](https://www.home-barista.com/espresso-machines/lelit-marax-t61215-350.html#p723763)
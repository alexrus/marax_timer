# MaraX Timer

> This project was designed to be used with a Lelit MaraX espresso machine.

***This repository is a rewrite of [espresso_timer](https://github.com/alexrus/espresso_timer) that has better doccumentation and is easyer to use.***

<div align="center">
    <img src="resources/ui.jpg" width="45%">
    <img src="resources/mini.jpg" width="45%">
</div>

## Hardware

- NodeMCU (ESP8266) like the [Wemos D1 Mini](https://www.alibaba.com/product-detail/D1-mini-V2-Mini-NodeMcu-4M_1600092270848.html)
- [0.96" oled display](https://www.alibaba.com/product-detail/0-96-inch-OLED-display-module_1600187274880.html)
- [Reed sensor](https://www.alibaba.com/product-detail/Magnetic-Reed-Switch-Proximity-Switch-Sensor_1918743677.html)
- 3d printed case ([3D Printer Monitor for Octoprint ESP8266 NodeMCU](https://www.thingiverse.com/thing:2937731)/[3D Printer Monitor for OctoPrint Wemos D1 ESP8266](https://www.thingiverse.com/thing:2884823))

## Software

In order to make NodeMCU working with Arduino IDE follow these instructions: [https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/](https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/). If you having troubles insalling the Github dependencies follow this guide: [Installing Arduino Library from GitHub](https://www.baldengineer.com/installing-arduino-library-from-github.html). 


This project uses the following dependencies:

* [https://github.com/adafruit/Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [https://github.com/adafruit/Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO)
* [https://github.com/adafruit/Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
* [https://github.com/knolleary/pubsubclient/](https://github.com/knolleary/pubsubclient/)
* [https://github.com/JChristensen/Timer](https://github.com/JChristensen/Timer)


## Hardware connections

### OLED wiring
You connect the oled display like this:
![](https://circuits4you.com/wp-content/uploads/2019/01/NodeMCU_ESP8266_OLED_Display.png)

### Reed sensor
- [Glue the reed switch onto the machine's vibration pump](resources/pump.jpg)
- The reed switch goes to ground and D7

### MaraX wiring

[Open the underside of the machine](http://www.youtube.com/watch?v=9NL6yeq7sMM) and you will see a [6 pin connector](https://preview.redd.it/mwf5u76b24751.jpg?width=3024&format=pjpg&auto=webp&s=e3af4370ee876cb590f7f007cb0ec9ed29688225).

- Connect pin 3 of the machine (RX) to pin D6 (TX) of nodeMCU
- Connect pin 4 of the machine (TX) to pin D5 (RX) of nodeMCU 

> *In case this does not work, change the pins connection (pin 3 to D5 & pin 4 to D6)*

## Operation

The timer display will power on and off with the MaraX.

### Shot Counter

When the pump will start, the timer on the screen will also start counting.

When the pump is stopped, the time will remain printed on the screen (if more that 12 seconds have passed) until the next time the pump is activated.

The time is not recorded unless 12 seconds have passed because MaraX machine starts the pump by itself from time to time to fill the boiler with water.

### MQTT

If you connect the ESP to the wifi and provide a MQTT bridge the following messages will be broadcasted:

- `/marax/power` with `on` or `off`
- `/marax/pump` with `on` or `off`
- `/marax/hx` with the current temperature of the heat exchanger
- `/marax/steam` with the current temperature of the steam boiler
- `/marax/shot` with the duration of the last shot (if the shot took longer than 15 seconds)

## Good Reads

- [More information about the project and progress](https://www.home-barista.com/espresso-machines/lelit-marax-t61215-350.html#p723763)
- [Data Visualisation - Lelit MaraX 'Mod'](https://www.reddit.com/r/Coffee/comments/hfsvep/data_visualisation_lelit_marax_mod/)
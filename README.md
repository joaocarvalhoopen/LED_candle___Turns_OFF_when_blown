# LED candle - Turns OFF when blown

## Schematic
![LED candle schematic](./LED_candle_schematic.png?raw=true "LED candle schematic")

## Description
This is an ESP32 microcontroller programed with Arduino, connected to a LED trough a 100 Ohms resistor. <br>
The LED is always on and the ADC pin of the microcontroller is monitoring the voltage drop of on the LED diode (forward PN junction voltage). When you blow to the LED the temperature lowers and the forward voltage becomes higher, so there is a raise in it in the order of 1 to 2 mV.  The way we determine this is by maintaining the current value and the last two values and calculating the ratio of voltage raise. The ADC of the ESP32 varies a lot so the average of 1000 measurements is needed to raise, the resolution and to smooth the value. You can monitor the voltage value or the difference in the ratio by connecting to the plot monitor tool in the Arduino IDE. After 2 seconds the LED turns on again. <br>
It works nicely. I made this small project for my daughter (12), with her and my nephew (11). The small box is powered by a small USB power bank. <br> 

## Final built for my daughter
![LED candle built](./image_LED_Candle_small.jpg?raw=true "LED candle built")

## License
MIT Open Source License.

## Have fun!
Best regards,<br>
Joao Nuno Carvalho    
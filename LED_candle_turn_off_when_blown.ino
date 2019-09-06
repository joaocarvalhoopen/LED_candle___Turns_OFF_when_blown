/* ****************************************************************************
 *                                                                            *
 *       LED candle the LED turns OFF when blown.                             *
 *                                                                            *
 ******************************************************************************
 * Author Joao Nuno Carvalho                                                  *
 * Author Diana     (12)                                                      *
 * Author Guilherme (11)                                                      *
 * Date: 2019.09.06                                                           *
 * License: MIT Open Source License.                                          *
 *                                                                            *
 * Description: This is an ESP32 microcontroller programed with Arduino,      *
 *              connected to a LED trough a 100 Ohms resistor.                *
 * The LED is always on and the ADC pin of the microcontroller is monitoring  *
 * the voltage drop of on the LED diode (forward PN junction voltage). When   *
 * you blow to the LED the temperature lowers and the forward voltage becomes *
 * higher, so there is a raise in it in the order of 1 to 2 mV.  The way we   *
 * determine this is by maintaining the current value and the last two values *
 * and calculating the ratio of voltage raise. The ADC of the ESP32 varies a  *
 * lot so the average of 1000 measurements is needed to raise, the resolution *
 * and to smooth the value. You can monitor the voltage value or the          *
 * difference in the ratio by connecting to the plot monitor tool in the      *
 * Arduino IDE. After 2 seconds the LED turns on again.                       *
 * It works nicely. I made this small project for my daughter (12), with her  *
 * and my nephew (11). The small box is powered by a small USB power bank.    *
 ******************************************************************************
*/


/*
 Board: ESP32

 Circuit:

 GPIO_12 -----------|
                    R
 GPIO_14 -----------|
                   LED 3MM Grinded
     GND -----------|

 R = 100 Ohms

*/

// LED connected to digital pin GPIO12.
int ledPin = 12;

// ADC pin connected from pin GPIO14 to measure the voltage drop of LED.
int ledAnalogIn  = 14;  
int sensor_value = 0;

// Sequence pattern detector.
int counter = 0;
float sensorValueAcumulator    = 0;
float sensor_value_minus_two   = 0;
float sensor_value_minus_one   = 0;

void setup(){
  pinMode (ledPin, OUTPUT);
  Serial.begin(115200);
  digitalWrite (ledPin, HIGH);
  // Wait 7 seconds to heat the LED and drop the voltage.
  delay(7000);
}

void loop(){
  // Delay to serve as barrier from the serial port comunications, to lower the noise on the ADC sampling.
  delay (100);
  sensorValueAcumulator = 0;

  for(int i=0; i<1000; i++){
    sensor_value = analogRead(ledAnalogIn);
    sensorValueAcumulator += sensor_value; 
  }
  sensorValueAcumulator /= 1000.0;
  // Delay to serve as barrier from the serial port comunications, to lower the noise on the ADC sampling.    
  delay (100);
  //Serial.println(sensorValueAcumulator);

  if (counter > 5){ // 10          
    float rate_2 = (sensorValueAcumulator - sensor_value_minus_two) / 2.0; 
    Serial.println(rate_2);
    if (rate_2 > 0.50) // 0.45
    {
      digitalWrite (ledPin, LOW);
      Serial.println("LED OFF");
      delay(2000);
      digitalWrite (ledPin, HIGH);
      counter = 0;
    }
  }
  sensor_value_minus_two   = sensor_value_minus_one;
  sensor_value_minus_one   = sensorValueAcumulator;
  counter++; 
}

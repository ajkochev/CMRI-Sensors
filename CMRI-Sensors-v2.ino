/* JMRI-CMRI Sensor Shield Sketch by Anthony Kochevar v2-10-2022
 * This sketch is for use with an Arduino Mega and Sensor Shield
 * Code maybe modified and distributed as long as it is done so freely.
 * Code is as is with no warranty implied or offered.
 *
 * ==Please read all comments below so you understand the sketch==
 *
 * For best performance only enable the number of sensors you need 
 * using numSensors.  If you only needed 30 
 * sensors, you'd set numSensors to 30 and use ports 3 to 33 on the 
 * shield.
 * The Analog ports will be used as well if numSensors is greater 
 * than 50 (the code adds a +3 offset to start on port 3).
 * A0 will start as port 54 and hardware address #054 in JMRI
 * ending with A15 being port 69 for a total of 67 ports.  
 *
 * Ports 0, 1 and 2 are not used as they are used internally 
 * for CMRI communication. 
 *
 * The JMRI +1 offset has also been taken into account in the sketch
 * and as such the hardware address in JMRI maps to the correct port.
 * If the CMRI node address was 3 the sensor on port 3 would have
 * hardware address 3003 in JMRI.  A sensor on port 45 would be 3045.
 * A sensor on port A10 (port 64) would be 3064.
*/

#include <CMRI.h>
#include <Auto485.h>


#define CMRI_ADDR 3 //CMRI node address in JMRI.  Change if needed.
#define DE_PIN 2  // Arduino pin used internally to CMRI communication.  Do not change.

Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 70, 0, bus);  // Initalize CMRI with up to 70 inputs and 0 outputs.

// numSensors sets the total number of sensors on the board you want to use.  Maximum is 67.
int numSensors = 67; 

//Below array is for use of the analog pins as digital sensors.  Do not change.
const int anaPin[16] = 
  { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 };

void setup() {
  Serial.begin(19200); 
  numSensors = numSensors + 3;  // Sets a +3 offset to account for starting on port 3.
  if (numSensors <= 53)  {  //  This if only runs if numServos is 53 or less
    for (int x = 3; x <= numSensors; x++) {
      pinMode(x, INPUT_PULLUP);
    }
  }
  if (numSensors >= 54) {  //  This if only runs if numServos is 54 and higher so Analog pins get initalized as well.
    for (int x = 3; x <= 53; x++) {
      pinMode(x, INPUT_PULLUP);
    }
    int a = numSensors - 53;
    for (int x = 0; x < a; x++) {
      pinMode(anaPin[x], INPUT_PULLUP);
    }
  }

}

void loop() {
  cmri.process();
  int a = 0;
  for (int x = 3; x < numSensors; x++) {
    if (x <= 53) cmri.set_bit(x-1, !digitalRead(x));  // x-1 is to account for JMRI offset.  Port 3 on board will now be address #003 in JMRI.
    if ((x > 53) && (x < numSensors)) {
      cmri.set_bit(x-1, !digitalRead(anaPin[a])); // x-1 is to account for JMRI offset.  Port A0 on board will start at #054 in JMRI.
      a++;
    } 
  }
}

# CMRI-Sensors
Input for up to 67 Sensors in JMRI via CMRI

JMRI-CMRI Sensor Shield Sketch by Anthony Kochevar v2-10-2022
This sketch is for use with an Arduino Mega and Sensor Shield
Code maybe modified and distributed as long as it is done so freely.
Code is as is with no warranty implied or offered.

==Please read all comments below so you understand the sketch==

For best performance only enable the number of sensors you need 
using numSensors.  If you only needed 30 
sensors, you'd set numSensors to 30 and use ports 3 to 33 on the 
shield.
The Analog ports will be used as well if numSensors is greater 
than 50 (the code adds a +3 offset to start on port 3).
A0 will start as port 54 and hardware address #054 in JMRI
ending with A15 being port 69 for a total of 67 ports.  

Ports 0, 1 and 2 are not used as they are used internally 
for CMRI communication. 

The JMRI +1 offset has also been taken into account in the sketch
and as such the hardware address in JMRI maps to the correct port.
If the CMRI node address was 3 the sensor on port 3 would have
hardware address 3003 in JMRI.  A sensor on port 45 would be 3045.
A sensor on port A10 (port 64) would be 3064.

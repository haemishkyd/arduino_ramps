# Controlling one motor with Arduino Mega, Ramps 1.4 and a NEMA 17

All the searches I have done on this topic seem to focus on setting the items mentioned up for a full 3D printer. These are very useful but if you want to use the hardware mentioned (because it is convenient) but you don't need the full setup with Marlin firmware etc, there seem to be very scant resources to accomplish this. This repo is to document my progress in trying to achieve just this.

## Parts List
* 1 x NEMA 17
* 1 x Ramps 1.4
* 1 x Arduino Mega
* 1 x A4988

## Connections
Stack the RAMPS board on top of the Arduino Mega. 

The RAMPS board has the following basic configuration:
![RAMPS Layout](https://github.com/haemishkyd/arduino_ramps/blob/master/RAMPS-connections.jpg)
image credit [NelisW](https://github.com/NelisW)

The A4988 needs to be placed onto the RAMPS. I have chosen to use Extruder Motor 1 for this project. The choice does not matter but the relevant pins will be required.
In the image above the top right hand pin of each drivers slot is GND.The bottom left will be EN. Orientate your stepper driver appropriately.
See the image below for the basic concept:
![My Setup](https://github.com/haemishkyd/arduino_ramps/blob/master/RAMPS_with_driver.jpg)

Next the NEMA 17 needs to be connected to the RAMPS board. The motor I had had the following configuration for the wire colours:
* Black: 1B
* Green: 1A
* Blue: 2A
* Red: 2B
I connected it as per the diagram below:
![Connections](https://github.com/haemishkyd/arduino_ramps/blob/master/NEMA_Connections.png)

## Software
The A4988 needs 3 main signals. 
* Enable
* Step
* Direction
The circuit diagram for the RAMPS board is provided here:

![RAMPS Circuit](https://github.com/haemishkyd/arduino_ramps/blob/master/RAMPS1.4schematic.png)

Since I have chosen E1 as my port on the RAMPS, the pins:
* E1-EN (D30)
* E1-DIR (D34)
* E1-STEP (D36) 
are the appropriate ones.
The pin E1-EN has a pull up which means to enable the driver you will need to phycially pull it down.

## Communications
Serial comms is the easiest way to get instructions to the board. The serial comms are accessed through AUX-1.
The diagram is given below:

![Ramps Gerber](https://github.com/haemishkyd/arduino_ramps/blob/master/ramps_layout.jpg)

D1 and D0 are the default serial port on the Arduino Mega.
* D0-Rx
* D1-Tx

Like so:

![Tx and Rx](https://github.com/haemishkyd/arduino_ramps/blob/master/serial_comms_RAMPS1.4.png)




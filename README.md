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

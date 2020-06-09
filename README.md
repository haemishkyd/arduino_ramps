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

Final connections are as follows:

![Final](https://github.com/haemishkyd/arduino_ramps/blob/master/final.jpg)

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

### Software Description
#### Setup
```
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  Serial.begin(115200);
  inputString.reserve(200);
```
  
  This setup code asigns the step, dir and enable pins as outputs. It also sets the serial baud rate.
#### Main Code Loop
```
    if (stringComplete == true){    
    String rotations = inputString.substring(1,5);
    String direction_data = inputString.substring(0,1);
    Serial.print(direction_data);
    float rotations_frac = rotations.toFloat();
    Serial.print(rotations_frac);
    inputString = "";
    stringComplete = false;
    digitalWrite(LED_BUILTIN, HIGH);
    if (direction_data.equals("F")){
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(dirPin,HIGH);
    }
    if (direction_data.equals("B")){
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(dirPin,LOW);
    }
    for(int x = 0; x < rotations_frac*1600; x++) {
      step();
    }
  }  
```

  The only intelligent bit in this code involves the parsing of the serial message. The direction pin is then determined by the serial message (forward 'F' or back 'B'). Since MS1, MS2 and MS3 are all jumpered, the actual numbers of steps per revolution is 1600. Hence the fraction sent is mutliplied by 1600.

#### Step Code
```
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(500); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(500); 
```
  This code literally pulses the stepper motor each time it is called.
  
## Communications
Serial comms is the easiest way to get instructions to the board. The serial comms are accessed through AUX-1.
The diagram is given below:

![Ramps Gerber](https://github.com/haemishkyd/arduino_ramps/blob/master/ramps_layout.jpg)

D1 and D0 are the default serial port on the Arduino Mega.
* D0-Rx
* D1-Tx

Like so:

![Tx and Rx](https://github.com/haemishkyd/arduino_ramps/blob/master/serial_comms_RAMPS1.4.png)

## Resources
[Connecting a NEMA17, Arguino Mega and A4988 without a RAMPS Board](https://howtomechatronics.com/tutorials/arduino/how-to-control-stepper-motor-with-a4988-driver-and-arduino/)



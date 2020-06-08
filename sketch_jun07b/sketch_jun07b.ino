/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
// defines pins numbers
const int stepPin = 36; 
const int dirPin = 34; 
const int enPin = 30;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
 
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  Serial.begin(115200);
  inputString.reserve(200);
}

void step(){
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(500); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(500); 
}

void loop() {
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
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

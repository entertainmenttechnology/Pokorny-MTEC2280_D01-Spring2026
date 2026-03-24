/*
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||                  "Serial Read - STRING"                           ||
||  Reads String value from Serial UART to control Piezo Frequency   ||
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

- Receives String Data over Serial UART port from P5 sketch
- Parses, or converts, the incoming String into integer

REFERENCE:
- https://docs.arduino.cc/language-reference/en/functions/communication/serial/read/
- https://docs.arduino.cc/language-reference/en/functions/communication/serial/available/
- https://docs.arduino.cc/language-reference/en/functions/communication/serial/parseInt/
- https://docs.arduino.cc/language-reference/en/functions/math/map/
- https://docs.arduino.cc/language-reference/en/functions/math/constrain/
*/

const int ledPin_1 = 4;     // led 1 pin
const int ledPin_2 = 5;     // led 2 pin

int inData = 0;         // variable for storing our incoming ASCII character
int ledPwm_1 = 0;       // LED 1 PWM 
int ledPwm_2 = 0;       // LED 2 PWM 
int currentTime = 0;    // variable to store current millis
int lastTime = 0;       // variable to store millis at moment of last event
int timerInterval = 5;  //amount of milliseconds for timer comparison

void setup() 
{
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() 
{
  if(Serial.available())  //if there is data available in the serial buffer...
  {
    inData = Serial.parseInt(); // read, parse into integer, and store the received value

    ledPwm_1 = map(inData, 0, 1000, 0, 255);  // map inData from 0-1000 to 0-255
    ledPwm_1 = constrain(ledPwm_1, 0, 255);   // limit ledPwm_1 to 0-255 range just in case

    ledPwm_2 = map(inData, 1000, 2000, 255, 0); // map inData from 1000-2000 to 255-0
    ledPwm_2 = constrain(ledPwm_2, 0, 255);     // limit ledPwm_2 to 0-255 range just in case
  }

  currentTime = millis(); //store current elapsed time
  if (currentTime - lastTime >= timerInterval) //if we have reached our timer interval...
  {
    lastTime = currentTime; //store time of event

    //Set LED PWM Duty Cycle
    analogWrite(ledPin_1, ledPwm_1);
    analogWrite(ledPin_2, ledPwm_2);
  }
}

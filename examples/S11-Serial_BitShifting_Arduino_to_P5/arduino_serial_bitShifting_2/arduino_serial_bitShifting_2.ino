/*
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
|||||||||||||||||||||||||||||||||||||||||||
||        "1 BYTE for 8 BUTTONS"         ||
||||||||||||||||||||||||||||||||||||||||||| 
  - We can send 8 digital sensor states as a single byte using Bit-Level Manipulation
  - this allow us to send more data with fewer bytes, which is more efficient for serial communication
  - Bi-Directional Serial Communication between Microcontroller & P5.JS
  - Tansmits(Tx) and Receives(Rx) Serial Data
  - Receives a control byte of ASCII character 'A'
  - Sends sensor data of a single Byte when 'A' control byte received
  
  FURTHER READING:
  https://docs.arduino.cc/language-reference/en/functions/communication/serial/parseInt/
  https://docs.arduino.cc/language-reference/en/structure/bitwise-operators/bitshiftRight/
  https://docs.arduino.cc/language-reference/en/structure/bitwise-operators/bitshiftLeft/
  https://docs.arduino.cc/language-reference/en/structure/bitwise-operators/bitwiseOr/
  https://docs.arduino.cc/language-reference/en/structure/bitwise-operators/bitwiseAnd/
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
*/

const int buttonPins[] = {1, 2, 42, 41, 40, 39, 38, 37}; //array of button pins
uint8_t outByte = 0;  //byte to hold button states, 8 bits for 8 buttons

void setup() 
{
  Serial.begin(9600); //open serial port at 9600bps

  for (int i = 0; i < 8; i++)  //for every button pin...
  {
    pinMode(buttonPins[i], INPUT_PULLUP); //set to input pullup mode
  }
}

void loop() 
{
  outByte = 0; //clear byte at start of each loop
  //VERY IMPORTANT: if we dont clear byte, bits set high once will never go low again

  for (int i = 0; i < 8; i++) //for every button...
  {
    outByte = outByte | !digitalRead(buttonPins[i]) << i; //read button and store in correct bit
    // the current state of button i is shifted to the left by i positions
    // the shifted value is then combined with outByte using a bitwise OR operation
    // this accumulates the states of all 8 buttons into a single byte
  }

  if(Serial.available()) //if data is available to read from serial port...
  {
    int inByte = Serial.read(); //store incoming byte in variable
    if (inByte == 'A')  //if incoming byte is ASCII character 'A'...
    {
      Serial.write(outByte);  //send the byte containing button states via serial port
    }
  }
}

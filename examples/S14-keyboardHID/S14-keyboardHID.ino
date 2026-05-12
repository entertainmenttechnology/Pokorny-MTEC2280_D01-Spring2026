/*
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
||||||||||||||||||||||||||
||    "Keyboard HID"    ||
||||||||||||||||||||||||||

- Turns microcontroller into a USB keyboard, a "Human-Interface-Device" or HID for short.

- button 1 = letter
- button 2 = message

- NOTE: You MUST set USB MODE to "USB-OTG (TinyUSB)" under Tools menu
- NOTE: you cannot use GPIO Pins 19 & 20 when using USB comms

REFERENCE:
https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/
https://docs.arduino.cc/built-in-examples/usb/KeyboardAndMouseControl/
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
*/

//include USB & Keyboard libraries
#include "USB.h"
#include "USBHIDKeyboard.h"

//include our own Button Class (this must be copied into arduino project folder)
#include "Button.h"

//Define Pins
const int buttonPin_1 = 1;
const int buttonPin_2 = 2;

//array of letters in alphabet
const char alphabet[] = 
{'a', 'b', 'c', 'd', 'e', 'f', 'g', 
'h', 'i', 'j', 'k', 'l', 'm', 'n', 
'o', 'p', 'q', 'r', 's', 't', 'u', 
'v', 'w', 'x', 'y', 'z'};

//alphabet array index
int letter = 0;

//create keyboard object
USBHIDKeyboard Keyboard;

// Create new button objects from Button class
Button button1(buttonPin_1, INPUT_PULLUP);
Button button2(buttonPin_2, INPUT_PULLUP);

void setup() 
{
  Serial.begin(9600); //start serial comm @ 9600 baud rate
  Keyboard.begin(); //init keyboard object
  USB.begin();  //init USB object
}

void loop() 
{
  //read and update button states
  button1.update();
  button2.update();

  if (button1.risingEdge())  //if rising edge detected...
  {

    Keyboard.write(alphabet[letter]); //send keyboard write command of a single char
    //you can also use Keyboard.print()

    letter++; //increment letter
    if (letter > 25) // if we have reached the end of the alphabet...
    {
      Keyboard.println(); //print a new line
      letter = 0; //reset letter to 0
    }
  }
  
  if (button2.risingEdge())  //if rising edge detected...
  {
    //print long message with newlines when button 2 is pressed
    Keyboard.println("Hello World,");
    Keyboard.println("This is a message from your ESP32 MCU using USB HID.");
    Keyboard.println("You can print out whole strings of text in one command!");
  }

  delay(12); //slight delay to remove button debounce noise
  //NOTE: add a proper timer for button debounce, delay() works for now
}
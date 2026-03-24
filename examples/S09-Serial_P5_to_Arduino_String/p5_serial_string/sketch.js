/*
P5.JS SERIAL SEND STRING

An example p5.js sketch that uses the p5.serialport library to send a string across serial port.
Fades between two PWM LEDs via serial comms.

MOUSE X POSITION = FADES BETWEEN BRIGHTNESS OF TWO LEDS
- When mouse is on left half of canvas, left LED is brighter.
- When mouse is on right half of canvas, right LED is brighter.
- When mouse is in middle of canvas, both LEDs are at equal brightness.
- When mouse is NOT pressed, the brightness of both LEDs will fade in and out.

- We can send any value or character we want to our Microntroller via.
- Useful when you want to use values larger than the 255 (8-bit) limit of serial.write() function.
- However, we will need to parse the string on the Microcontroller into an integer (see Arduino_Serial_String.ino).

This code is designed to work with the "Arduino_Serial_String" example sketch.

NOTES:
- You must run and establish a serial connection with p5.serialcontrol app to use this code:
  https://github.com/p5-serial/p5.serialcontrol/releases/tag/0.1.2

- Remember to add the p5.serialport library to your index.html file. Add this line below <script src="libraries/p5.min.js"></script>:

    <script language="javascript" type="text/javascript" src="https://cdn.jsdelivr.net/npm/p5.serialserver@0.0.28/lib/p5.serialport.js"></script>

- Make sure the baud rate in options matches the baud rate in your Arduino code.
- Remember to change the portName variable to match your own serial port.
*/

let serial; // variable for instance of the serialport library
let portName = '/dev/tty.usbserial-213320'; // fill in your serial port name
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code
let outVal = 0; // value to be sent via serial
let rate = 40; // variable to control speed and direction of fading effect

function setup() 
{
  //P5.JS Setup
  createCanvas(800, 400);

  //P5 SerialPort Setup
  serial = new p5.SerialPort();             // make a new instance of the serialport library
  serial.on('list', printList);             // set a callback function for the serialport list event
  serial.on('connected', serverConnected);  // set callback for connecting to the server
  serial.on('open', portOpen);              // set callback for the port opening
  serial.on('data', serialEvent);           // set callback for when new data received
  serial.on('error', serialError);          // set callback for errors
  serial.on('close', portClose);            // set callback for closing the port
  serial.list();                            // list the serial ports
  serial.open(portName, options);           // open a serial port
}

function draw() 
{
  background(0, 4); // black background with low opacity for trailing effect
  
  if(mouseIsPressed)  //if mouse is pressed...
  {
    fill(0, 255, 0, 4);                     // set green fill color with transparency
    rect(0, 0, width/2, height);            // draw rectangle on left half of canvas
    fill(255, 255, 0,4);                    // set yellow fill color with transparency
    rect(width/2, 0, width, height);        // draw rectangle on right half of canvas
    fill(255);                              // set white stroke color with some transparency
    circle(mouseX, height/2, 127);          // draw circle at mouse position
    xPos = constrain(mouseX, 0, width);     // constrain xPos to canvas width
    outVal = map(xPos, 0, width, 0, 2000);  // map xPos to 0  to 2000
    outVal = floor(outVal);                 // convert to integer by cutting off decimal
    print(outVal);                          // print the output value to the console for debugging
  }
  else  //if mouse is not pressed...
  {
    outVal += rate; //adjust outVal by adding rate for fading effect

    if (outVal <= 0 || outVal >= 2000) // if outVal goes outside of range, change direction
    {
      rate *= -1; // change rate direction
    }

    print(outVal); // print the output value to the console for debugging
  }

  serial.write(outVal + '/n'); //convert to string, and send via serial with newline character at end of message

    /*
    by adding the newline '/n' character to serial.write message, we are:
    - converting the integer outVal into a string through concatenation.
    - adding a delimiter of newline character so that arduino side will know when the message ends.
    */
}

function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}

function portClose() //gets called when the serial port closes
{
  print("SERIAL PORT CLOSED");
}

function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serialEvent() // gets called when new serial data arrives
{
  //only sending data to microcontroller in this sketch, so not being used
}

function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}
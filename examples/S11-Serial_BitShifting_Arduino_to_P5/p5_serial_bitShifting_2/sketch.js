/*
P5.JS SERIAL BITSHIFTING EXAMPLE

An example p5.js sketch that uses the p5.serialport library to receive 8 digital sensor states across serial port.
Bidirectional Serial communication is established between P5.JS sketch and the ESP32 microcontroller.
Receives(Rx) 8bit value from arduino and Transmits(Tx) control byte from P5 via Serial UART.

This code is designed to work with the "arduino_serial_bitshifting_2" example sketch.

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

let buttons = [0, 0, 0, 0, 0, 0, 0, 0]; // array to hold the state of each bit button
let distance = 150; // distance from center to button circles

function setup() 
{
  //P5 Sketch Setup
  createCanvas(500, 500);
  textAlign(LEFT, CENTER);

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
  background(0); //clear frame
  translate(width/2, height/2); //move origin to center of canvas
  for (let i = 0; i < buttons.length; i++)  //for every button...
  {
    if(buttons[i]) //if button is on...
    {
      fill(255, 255, 100); //yellow fill
    }
    else
    {
      fill(64, 64, 64); //dark gray fill
    }

    circle(cos(i * TWO_PI / buttons.length) * distance, sin(i * TWO_PI / buttons.length) * distance, 100); //draw button circles in a circle
  }
}

function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");

  serial.write('A'); // send a byte to the microcontroller to let it know we are ready to receive data
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
  let inByte = serial.read(); // read one byte

  for (let i = 0; i < 8; i++)
  {
    let bitMask = 1 << i; // create a mask for the current bit position
    // for example, when i = 0, mask = 00000001, when i = 1, mask = 00000010, etc.

    buttons[i] = boolean(inByte & bitMask);
  }
  print("Received Byte: " + inByte);
  print("Button States: " + buttons);
  
  serial.write('A'); // send a byte to the microcontroller to let it know we are ready to receive the next byte
}

function serialError(err) //gets called when there's an error
{
  print('SERIAL ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERIAL SERVER");
}
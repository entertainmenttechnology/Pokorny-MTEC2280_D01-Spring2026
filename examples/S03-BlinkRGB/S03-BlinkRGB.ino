/*
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
  BlinkRGB

  - Demonstrates usage of onboard RGB LED on ESP32-S3 dev boards.
  - RGB LED @ GPIO Pin 38
  - There is a library for the RGB LED provided in the ESP framework.
  - library provides the function RGBLedWrite:
  void rgbLedWrite(int pin, int red_val, int green_val, int blue_val)
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
*/
const int pinRGB = 38;
int brightness = 4; //max is 255, very bright!
int delayTime = 1000;

void setup() 
{
  //typically you need to set LED pinMode to OUTPUT...
  //...but we are using a library that takes care of that for us.
}

// the loop function runs over and over again forever
void loop() 
{
  rgbLedWrite(pinRGB, brightness, brightness, brightness);  // White
  delay(delayTime);
  rgbLedWrite(pinRGB, brightness, 0, 0);  // Red
  delay(delayTime);
  rgbLedWrite(pinRGB, 0, brightness, 0);  // Green
  delay(delayTime);
  rgbLedWrite(pinRGB, 0, 0, brightness);  // Blue
  delay(delayTime);
  rgbLedWrite(pinRGB, brightness, brightness, 0);  // Yellow
  delay(delayTime);
  rgbLedWrite(pinRGB, brightness, 0, brightness);  // Magenta
  delay(delayTime);
  rgbLedWrite(pinRGB, 0, brightness, brightness);  // Cyan
  delay(delayTime);
}

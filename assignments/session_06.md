
## SESSION 06

## MIDTERM DUE 5/11
See [MIDTERM]() for more info.

### Familiarize yourself with:

* [analogWrite()](https://www.arduino.cc/reference/tr/language/functions/analog-io/analogwrite/)

* [tone()](https://docs.arduino.cc/language-reference/en/functions/advanced-io/tone/)

* [analogWriteFrequency()](https://randomnerdtutorials.com/esp32-pwm-arduino-ide/) - NOTE: this is ESP32 specific

* [Installing Libraries in Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/)

* [Servo Motors](https://docs.arduino.cc/learn/electronics/servo-motors/)

NOTE:     
Since we are using an ESP32 board, the standard Arduino Servo library won't work.        
We can use the "[ESP32Servo](https://github.com/madhephaestus/ESP32Servo/tree/master)" library by Kevin Harrington/John Bennett.     
It works in much the same way as Servo, you just need to install the library in Arduino IDE's library manager, and #include <ESP32Servo.h> instead of <Servo.h> at top of sketch.
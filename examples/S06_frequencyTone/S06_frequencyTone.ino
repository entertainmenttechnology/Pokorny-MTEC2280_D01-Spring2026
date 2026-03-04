/*
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
||||||||||||||||||||||||||||||||||||||||||
  ||       "MUSIC TO MY EARS"         ||
  ||      Generating Sound w/ PWM     ||
  ||       by Ian Pokorny             ||
  ||         MTEC-2280                ||
||||||||||||||||||||||||||||||||||||||||||
- Plays a looping melody with tone()
- uncomment lower portion, and comment out upper tone portion for experimental sounds

CIRCUIT:
- piezo buzzer connected to pin 1 and GND

REFERENCE:
- https://docs.arduino.cc/language-reference/en/functions/advanced-io/tone/

<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
*/

const int piezoPin = 1; //piezo buzzer connected to pin 1

bool intro = 0; //boolean variable to track whether we've played the intro melody yet

int octave = 2; //octave variable. we can multiply this by the base frequency to shift the pitch up or down by octaves. 
                // for example: 110 * octave will be 110Hz in octave 1, 220Hz in octave 2, 440Hz in octave 4, etc.

void setup() 
{
  Serial.begin(115200); //start serial communication at 115200 baud
}

void loop() 
{
  //tone(pin, frequency in Hz, duration in millisecond)

  if(!intro)  //if we haven't played intro yet...
  { 
    //play intro melody. 
    tone(piezoPin, 1000, 100);
    tone(piezoPin, 1100, 100);
    tone(piezoPin, 1200, 100);
    tone(piezoPin, 1300, 100);
    tone(piezoPin, 1400, 100);
    tone(piezoPin, 1500, 100);
    tone(piezoPin, 1400, 100);
    tone(piezoPin, 1300, 100);
    tone(piezoPin, 1200, 100);
    tone(piezoPin, 1100, 100);
    tone(piezoPin, 1000, 100);
    tone(piezoPin, 1200, 100);
    tone(piezoPin, 1400, 100);
    tone(piezoPin, 1600, 100);
    tone(piezoPin, 1800, 100);
    tone(piezoPin, 2000, 100);
    tone(piezoPin, 2200, 200);
    tone(piezoPin, 2400, 300);
    tone(piezoPin, 2600, 400);
    tone(piezoPin, 2800, 500);
    tone(piezoPin, 2600, 600);
    tone(piezoPin, 2400, 700);
    
    intro = 1;  //set intro to true so it doesn't play again
  }

  //main melody
  tone(piezoPin, 90 * octave, 500);
  tone(piezoPin, 100 * octave, 500);
  tone(piezoPin, 110 * octave, 500);

  tone(piezoPin, 110 * octave, 500);
  tone(piezoPin, 220 * octave, 1000);
  tone(piezoPin, 110 * octave, 200);
  tone(piezoPin, 440 * octave, 1000);
  tone(piezoPin, 660 * octave, 200);
  tone(piezoPin, 220 * octave, 200);

  tone(piezoPin, 110 * octave, 500);
  tone(piezoPin, 100 * octave, 500);
  tone(piezoPin, 90 * octave, 500);
}
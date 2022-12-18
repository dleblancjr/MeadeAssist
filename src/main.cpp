#include <Arduino.h>

// constants
int digitalLed = 13;
uint8_t digitalOn  = 0;
int analogLed = 9;
int fadeAmount = 1;
int brightness = 5;
int second = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(digitalLed, OUTPUT);
  pinMode(analogLed, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  // set the brightness of pin 9:
  analogWrite(analogLed, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 5 || brightness >= 100)
  {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect

  if (brightness % 25 == 0)
  {
    if (digitalOn == 0)
    {
      digitalWrite(digitalLed, LOW);
      digitalOn = 1;
    }
    else
    {
      digitalWrite(digitalLed, HIGH);
      digitalOn = 0;
    }
  }

  delay(10);
}
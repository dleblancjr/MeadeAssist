#include <Arduino.h>
#include "main.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED FeatherWing buttons map to different pins depending on board.
// The I2C (Wire) bus may also be different.
#if defined(ESP8266)
#define BUTTON_A 0
#define BUTTON_B 16
#define BUTTON_C 2
#define WIRE Wire
#elif defined(ESP32)
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#define WIRE Wire
#elif defined(ARDUINO_STM32_FEATHER)
#define BUTTON_A PA15
#define BUTTON_B PC7
#define BUTTON_C PC5
#define WIRE Wire
#elif defined(TEENSYDUINO)
#define BUTTON_A 4
#define BUTTON_B 3
#define BUTTON_C 8
#define WIRE Wire
#elif defined(ARDUINO_FEATHER52832)
#define BUTTON_A 31
#define BUTTON_B 30
#define BUTTON_C 27
#define WIRE Wire
#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
#define BUTTON_A 9
#define BUTTON_B 8
#define BUTTON_C 7
#define WIRE Wire1
#else // 32u4, M0, M4, nrf52840 and 328p
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5
#define WIRE Wire
#endif
// constants
int OLED_RESET = -1;
int DISPLAY_ADDRESS = 0x3C;
int digitalLed = 13;
uint8_t onBoardDigitalOn  = 0;
int second = 1000;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  log({"Starting ..."});

  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS); // Address 0x3C for 128x32

  display.display();
  // delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Connected\n");
  display.print("Connected");
  display.setCursor(0, 0);
  display.display(); // actually display all of the above

  setOnBoardLED(onBoardDigitalOn);

  log({"Starting complete."});
  // writeToI2C(displayAddress, {"Starting complete."});
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(500);

  
}

void setOnBoardLED( bool isOn) {
  if (isOn == 0)
  {
    digitalWrite(digitalLed, LOW);
  }
  else
  {
    digitalWrite(digitalLed, HIGH);
  }
}

void log(char string[50])
{
  Serial.print(string);
  Serial.print("\n");
}

void writeToI2C( int address, char string[50]) {
  Wire.beginTransmission(address);
  Wire.write(string);

  Wire.endTransmission(true);
}
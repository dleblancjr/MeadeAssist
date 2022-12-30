#include <Arduino.h>
#include "main.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "I2C.h"
#include <MPU9250_asukiaaa.h>
#include <SoftwareSerial.h>

MPU9250_asukiaaa mpu9250;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

// constants

const int DISPLAY_ADDRESS = 0x3C;
const int digitalLed = 13;
const int second = 1000;
const int LINE_HEIGHT = 8;

int OLED_RESET = -1;
int onBoardDigitalOn = 0;
uint8_t sensorId;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

// Create a software serial port called "gpsSerial"
SoftwareSerial *gpsSerial;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
  {
    delay(1);
  };

  pinMode(gpsRXPin, INPUT);
  pinMode(gpsTXPin, OUTPUT);
  gpsSerial = new SoftwareSerial(gpsRXPin, gpsTXPin);
  gpsSerial->begin(gpsBaud);

  log({"Starting ..."});
  initDisplay();

  int result = 1;
  display.clearDisplay();

  result = mpu9250.readId(&sensorId);
  if (result == 0)
  {
    displaySensorId(sensorId);
  }
  else
  {
    Serial.println("Cannot read sensorId " + String(result));
  }

  // Start the software serial port at the GPS's default baud
  // gpsSerial.begin(gpsBaud);

  setOnBoardLED(onBoardDigitalOn);
  // MPU 9550
  log({"Starting MPU9550."});

  if (true)
  {
    mpu9250.beginAccel();
    mpu9250.beginGyro();
    mpu9250.beginMag();
  }

  log({"Starting complete."});
}

void loop()
{
  display.clearDisplay();
  int result = mpu9250.accelUpdate();
  if (result == 0)
  {
    // displayLevel(mpu9250.accelZ());

    // positive X is right side down, negative X is left side down
    aX = mpu9250.accelX();

    // positive Y is front up, negative Y is front down
    aY = mpu9250.accelY();

    // should be 1 when flat
    aZ = mpu9250.accelZ();
    //  aSqrt = mpu9250.accelSqrt();

    displayAccel(aX, aY, aZ);
  }
  else
  {
    Serial.println("Can not read accel values " + String(result));
  }

  // result = mpu9250.gyroUpdate();
  // if (result == 0)
  // {
  //   gX = mpu9250.gyroX();
  //   gY = mpu9250.gyroY();
  //   gZ = mpu9250.gyroZ();

  //   displayGyro(gX, gY, gZ);
  // }
  // else
  // {
  //   Serial.println("Cannot read gyro values " + String(result));
  // }

  result = mpu9250.magUpdate();
  if (result == 0)
  {
    // displayDirection(mpu9250.magX());
    displayDirection(mpu9250.magHorizDirection());

    // mX = mpu9250.magX();
    // mY = mpu9250.magY();
    // mZ = mpu9250.magZ();
    // mDirection = mpu9250.magHorizDirection();
    // displayMag(mX, mY, mZ, mDirection);
  }
  else
  {
    Serial.println("Cannot read mag values " + String(result));
  }

  display.display();
  delay(250);
}

void setOnBoardLED(bool isOn)
{
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

void print_roll_pitch_yaw()
{
  // display.setCursor(0, 0);
  // display.print("Yaw: ");
  // display.print(mpu.getYaw(), 2);
  // display.print(",  Pitch: ");
  // display.print(mpu.getPitch(), 2);
  // display.print(",  Roll: ");
  // display.print(mpu.getRoll(), 2);
  // display.setCursor(0, 0);
  // display.display(); // actually display all of the above

  // Serial.print("Yaw: ");
  // Serial.print(mpu.getYaw(), 2);
  // Serial.print(",\n");
  // Serial.print("Pitch: " ) ;
  //  Serial.print(mpu.getPitch(), 2);
  //  Serial.print(",\n");
  //  Serial.print(" Roll: ");
  //  Serial.println(mpu.getRoll(), 2);
}

void initDisplay()
{
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS); // Address 0x3C for 128x32

  display.display();

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  delay(2000);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  // display.setTextColor(GREEN);
  display.setCursor(0, 0);
  display.print("Connected");
  display.setCursor(0, 0);
  display.display(); // actually display all of the above
}

void displaySensorId(int id)
{
  display.setCursor(0, 0);
  display.print("MPU9250 ID: " + String(id));
  display.setCursor(0, LINE_HEIGHT);
  display.print("Item:  X     Y     Z");
  display.display();
}

void displayAccel(float x, float y, float z)
{
  display.setCursor(0, LINE_HEIGHT * 2);
  display.print("XL:" + String(x) + "," + String(y) + "," + String(z));
  display.display();
}

void displayGyro(float x, float y, float z)
{
  display.setCursor(0, LINE_HEIGHT * 3);
  display.print("GR:" + String(x) + "," + String(y) + "," + String(z));
  display.display();
}

void displayMag(float x, float y, float z, float mDirection)
{
  // display.setCursor(0, LINE_HEIGHT * 4);
  // display.print("MG:" + String(x) + "," + String(y) + "," + String(z));
  // display.setCursor(0, LINE_HEIGHT * 5);
  // display.print("Horz Dir: " + String(mDirection));
  // display.display();

  display.setCursor(0, LINE_HEIGHT * 4);
  display.print("Direction:" + String(x));
  display.display();
}

void displayLevel(float z)
{
  display.setCursor(0, LINE_HEIGHT * 2);
  display.print("Level: " + String(z));
}

void displayDirection(float x)
{
  display.setCursor(0, LINE_HEIGHT * 3);
  display.print("Direction " + String(x));
}
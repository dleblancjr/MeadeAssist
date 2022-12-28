#define MPU9250_IMU_ADDRESS 0x68
#define MPU9250_MAG_ADDRESS 0x0C


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

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

void setOnBoardLED(bool isOn);
void log(char string[50]);
void writeToI2C(int address, char string[50]);
void print_roll_pitch_yaw();
void initDisplay();
void displaySensorId(int id); 
void displayAccel(float x, float y, float z);
void displayGyro(float x, float y, float z);
void displayMag(float x, float y, float z, float mDirection);
void displayLevel(float z);
void displayDirection(float x);
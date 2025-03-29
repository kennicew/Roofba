/*
 * Main 
 * 
 * Contains Kennice's bluetooth code integrated with motor functions by Oscar and Jacqueline
 * Bluefruit library and sample code: https://learn.adafruit.com/introducing-the-adafruit-bluefruit-le-uart-friend/software
 * Bluefruit controller app reference: https://learn.adafruit.com/bluefruit-le-connect/controller#control-pad-2923571
 */

// bluetooth definitions
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"
#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

// Pin configurations for Arduino UNO software serial
#define BLUEFRUIT_SWUART_RXD_PIN       9  
#define BLUEFRUIT_SWUART_TXD_PIN       10  
#define BLUEFRUIT_UART_CTS_PIN         11 
#define BLUEFRUIT_UART_RTS_PIN         8   

// Define bluetooth firmware properties
#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"


// Create bluefruit Software Serial object
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN); 
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

// importing functions from packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// importing functions from integrate.cpp
void turnLeft();
void integrateSetup();
void moveServo(int position);
void stopMotors();
void beginmotors();
void backwards();
void turnLeft();
void turnRight();
void changedirection();
void ultrasonicSensing();

extern uint8_t packetbuffer[]; // defining data array received from Bluefruit module

// A small helper function to prints error message to Serial and halt execution
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void)
{
  //Initialize motors setup
  integrateSetup();

  //Bluetooth setup
  while (!Serial);  // Wait for serial
  delay(500);

  Serial.begin(115200); // Set serial to poart 115200 specifically for bluetooth-serial communication

  // Initialize Bluefruit module
  Serial.print(F("Initialising the Bluefruit LE module: "));

  // Error for debugging when Serial cannot connect to Bluefruit module
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  // If bluetooth connection is established with serial, print OK
  Serial.println( F("OK!") );
  
  }

  ble.echo(false); // Disable command echo from Bluefruit
  ble.verbose(false);  // Reduce debug output

  // Wait for connection when Bluefruit is not connected
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("******************************"));

  // Configure LED behavior if firmware supports it
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));

}

void loop(void) // Constantly poll for new command or response data
{
  // Check for new Bluetooth data
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;

  // Emergency stop if disconnected
  if (! ble.isConnected()) {
      stopMotors(); 
  }

  // Handle button pressed commands
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    Serial.print ("Button "); Serial.print(buttnum); //Print the button number in serial
    
    if (pressed) {
      Serial.println(" pressed");
      if (buttnum == 5) {
        beginmotors();  // Call forward function
      } else if (buttnum == 6) {
          backwards(); // Call backward function
      } else if (buttnum == 7) {
          turnLeft();  // Call left function
      } else if (buttnum == 8) {
          turnRight();  // Call right function
      } 
    } else {
      Serial.println(" released");
      stopMotors(); // Stop the rover if no buttons are pressed
    }
  }

  delay(5);

  // Button mapping reference:
  // up -> 5
  // down -> 6
  // right -> 8
  // left -> 7
  
  //ultrasonicSensing(); // Optional ultrasonic sensing (commented out for motor testing to reduce delays)
}

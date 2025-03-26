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

    #define FACTORYRESET_ENABLE         0
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"

    // SOFTWARE UART SETTINGS
  #define BLUEFRUIT_SWUART_RXD_PIN       9    // Required for software serial!
  #define BLUEFRUIT_SWUART_TXD_PIN       10   // Required for software serial!
  #define BLUEFRUIT_UART_CTS_PIN         11   // Required for software serial!
  #define BLUEFRUIT_UART_RTS_PIN         8   // Optional, set to -1 if unused
  
/*=========================================================================*/

// Create the bluefruit object, either software serial...uncomment these lines

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// Calling integrate functions
//void turnLeft();

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

void turnLeft();


/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
//void setup(void)
//{
//  while (!Serial);  // required for Flora & Micro
//  delay(500);
//
//  Serial.begin(115200);
//  Serial.println(F("Adafruit Bluefruit App Controller Example"));
//  Serial.println(F("-----------------------------------------"));
//
//  /* Initialise the module */
//  Serial.print(F("Initialising the Bluefruit LE module: "));
//
//  if ( !ble.begin(VERBOSE_MODE) )
//  {
//    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
//  }
//  Serial.println( F("OK!") );
//
//  if ( FACTORYRESET_ENABLE )
//  {
//    /* Perform a factory reset to make sure everything is in a known state */
//    Serial.println(F("Performing a factory reset: "));
//    if ( ! ble.factoryReset() ){
//      error(F("Couldn't factory reset"));
//    }
//  }
//
//
//  /* Disable command echo from Bluefruit */
//  ble.echo(false);
//
//  Serial.println("Requesting Bluefruit info:");
//  /* Print Bluefruit information */
//  ble.info();
//
//  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
//  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
//  Serial.println();
//
//  ble.verbose(false);  // debug info is a little annoying after this point!
//
//  /* Wait for connection */
//  while (! ble.isConnected()) {
//      delay(500);
//  }
//
//  Serial.println(F("******************************"));
//
//  // LED Activity command is only supported from 0.6.6
//  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
//  {
//    // Change Mode LED Activity
//    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
//    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
//  }
//
//  // Set Bluefruit to DATA mode
//  Serial.println( F("Switching to DATA mode!") );
//  ble.setMode(BLUEFRUIT_MODE_DATA);
//
//  Serial.println(F("******************************"));
//
//}

void loop(void) // Constantly poll for new command or response data
{
  /* Wait for new data to arrive */
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;

  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    Serial.print ("Button "); Serial.print(buttnum);
    if (pressed) {
      Serial.println(" pressed");
    } else {
      Serial.println(" released");
    }
    // Case statement to call motor controls - KW
    if (buttnum == 7) {
      turnLeft();
    }
//    if (buttnum == 5) {
//        turnLeft();  // Call forward function
//    } else if (buttnum == 6) {
//        stopMotors(); // Call backward function
//    } else if (buttnum == 7) {
//        turnleft();  // Call left function
//    } else if (buttnum == 8) {
//        turnRight();  // Call right function
//    }

  //Figure out which button is what, use an if statement to call the motor functions
  // up -> 5
  // down -> 6
  // right -> 8
  // left -> 7
  

}

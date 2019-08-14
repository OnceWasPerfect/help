#include "RadioSetup.h"  //Radio setup routine
#include <Adafruit_LIS3DH.h>  //Accelerometer library
#include <Adafruit_Sensor.h>  //Accelerometer library
#include <SPI.h>  //SPI hardware library

//Debug setup
#define DEBUG //comment out to disable debug
#ifdef DEBUG
 #define DEBUG_PRINT(x)     Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
 #define DEBUG_BEGIN(x)     Serial.begin(x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x) 
 #define DEBUG_BEGIN(x)
#endif

//Setup up a struct to pass the data
typedef struct data
{
  int x;  //Will hold the x axis info
  int y;  //Will hold the y axis info
};
data receivedLocation;  //create data object

//Stuff for radio
uint8_t rxbuf[RH_NRF24_MAX_MESSAGE_LEN];  //Set up the receive buffer
uint8_t rxbuflen = sizeof(rxbuf); //size of buffer


//Accelerometer setup
Adafruit_LIS3DH lis = Adafruit_LIS3DH();  //Create acc object

void setup()
{
  DEBUG_BEGIN(115200);
  //Radio setup
  radioSetup();
}

void loop()
{
  if(nrf24.recv(rxbuf, &rxbuflen)) //Receive the radio payload
  {
    memcpy(&receivedLocation, rxbuf, sizeof(receivedLocation));  //copy the payload to location 
    //receivedLocation = (struct data *)rxbuf; 
    DEBUG_PRINT("Received X = ");DEBUG_PRINT(receivedLocation.x);DEBUG_PRINT(" Received Y = ");DEBUG_PRINTLN(receivedLocation.y);
    //return true;
  }  
  else
  {
    DEBUG_PRINTLN("readRadio failed");
    //return false;
  }
  delay(100);  
}
  

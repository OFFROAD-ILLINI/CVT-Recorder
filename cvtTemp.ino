//Mostly copied from https://www.milesburton.com/Dallas_Temperature_Control_Library#Code.2FLibrary
#include <OneWire.h>

#include <DallasTemperature.h>

#include <SPI.h>
#include <SD.h>
 
// Data wire is plugged into pin 2 on the Arduino

#define ONE_WIRE_BUS 2

 

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

OneWire oneWire(ONE_WIRE_BUS);

 

// Pass our oneWire reference to Dallas Temperature.

DallasTemperature sensors(&oneWire);

 

void setup(void) {

  // start serial port

  Serial.begin(9600);

  // Now I'm copying even more code to write to SD card
  // https://www.arduino.cc/en/Tutorial/ReadWrite
  // Note that this is configured for use with Ethernet Shield
  /*
  * The circuit:
  * SD card attached to SPI bus as follows:
  ** MOSI - pin 11
  ** MISO - pin 12
  ** CLK - pin 13
  ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
  */



  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  Serial.println("CVT Temp Testing");
  
  // Start up the library

  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement

}
 

void loop(void) {

  // call sensors.requestTemperatures() to issue a global temperature

  // request to all devices on the bus

  Serial.print("Requesting temperatures...");

  sensors.requestTemperatures(); // Send the command to get temperatures

  Serial.println("DONE");

 

  Serial.print("Temperature for Device 1 is: ");

  //Storing temperature in Celsius

  float cvtTemp = sensors.getTempCByIndex(0);

  Serial.print(cvtTemp); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File tempFile = SD.open("cvtTemp.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (tempFile) {
    tempFile.println(cvtTemp);
    tempFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening cvtTemp.txt");
  }
}
 



 

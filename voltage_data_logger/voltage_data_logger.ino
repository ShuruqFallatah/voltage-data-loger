
#include <SPI.h>
#include <DS3231.h>

File myFile;
DS3231 rtc(SDA, SCL);
int pinCS = 53; // Pin 10 on Arduino Uno




void setup() {
   
  Serial.begin(9600);
  Serial.print("DATA LOGGER");
  pinMode(pinCS, OUTPUT);
  analogReference(DEFAULT);
 
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  rtc.begin();    
}
void loop() {
  Serial.print(rtc.getTimeStr());
  Serial.print(",");
  Serial.println(int(rtc.getTemp()));

//-------------------------------------------------------------
  float v = (float) 0.0047 * analogRead(A0) + 0.1599;
  Serial.println(v, 2);
  delay(1000);

Serial.println("----------------------");
//-------------------------------------------------------------
 
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {  
    myFile.print(rtc.getTimeStr());
    myFile.print(",");    
    myFile.print(int(rtc.getTemp()));
    myFile.println(",");
 
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  delay(2000);
}



#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>    //If you don't have the LiquidCrystal_I2C library, download it and install it
LiquidCrystal_I2C lcd(0x27,16,2);
float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(8,9);//tx,rx
SoftwareSerial gsmm(2,3);//tx,rx
TinyGPSPlus gps;// create gps object
void setup(){
Serial.begin(9600);
  lcd.init();
  lcd.backlight();// connect serial
//lcd.begin(16, 2);
gpsSerial.begin(9600);
gpsSerial.listen();
 textgps();
 gsmm.begin(9600);
  gsmm.print("\r");
  delay(1000);                  
  gsmm.print("AT+CMGF=1\r");    
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
  gsmm.print("AT+CMGS=\"+919342135347\"\r");    
  delay(1000);
  //The text of the message to be sent.
  //gsmm.print(lattitude,longitude);
// gsmm.print(lattitude); 
//  gsmm.print(longitude); 
  gsmm.print("https://www.google.com/maps/place/");
      gsmm.print(lattitude, 6);
      gsmm.print(",");
      gsmm.print(longitude, 6);
  
  delay(1000);
  gsmm.write(0x1A);
  delay(1000); 
// connect gps sensor


}
void loop(){
  

}

void textgps()
{

    while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
      break;
      }
  
   
  
}

 Serial.print("LATTITUDE="); Serial.println(lattitude,6);
 Serial.print("LONGITUDE="); Serial.println(longitude,6);
 lcd.print("LAT ");lcd.print(lattitude,6);
 lcd.setCursor(0, 1);
 lcd.print("LONG ");lcd.print(longitude,6);
 delay(1000);
// lcd.clear();
}

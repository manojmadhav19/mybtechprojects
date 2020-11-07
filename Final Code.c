#include <TinyGPS++.h> 
#include <SoftwareSerial.h> 
/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial GPS_SoftSerial(9, 10);/* (Rx, Tx) */ 
/* Create an object named gps of the class TinyGPSPlus */ 
TinyGPSPlus gps; 
 
volatile float minutes, seconds; 
volatile int degree, secs, mins; 
volatile int green=11; /*WARNING LED*/ 
volatile int red=2; /*SAFE LED*/ 
volatile int blue=13; 
double x,y; 
 
void setup() { 
 Serial.begin(9600); /* Define baud rate for serial 
communication */ 
  GPS_SoftSerial.begin(9600); /* Define baud rate for software 
serial communication */ 
  pinMode(green,OUTPUT); 
  pinMode(red,OUTPUT); 
  pinMode(blue,OUTPUT); 
}
void loop() { 
 
       LatLong(); 
      Serial.println(x,6); 
       Serial.println(y,6); 
 
 if(0.0002*x-0.0006*y>=0.0083257 && y>12.841591 && 
y<12.841731 && x>80.153035 && x<80.153683) // VIT CHENNAI 
PARKING LOT 
       { 
        warn(); 
       } 
 else if(0.0001*x+0.001*y>=0.0208571 && y>12.841687 && 
y<12.841731 && x>80.153683 && x<80.154636) //VIT CHENNAI MGR 
STATUE 
       { 
        warn(); 
       } 
       else 
       safe();  
} 
 
static void smartDelay(unsigned long ms) 
{ 
  unsigned long start = millis(); 
  do 
  { 
 while (GPS_SoftSerial.available()) /* Encode data read 
from GPS while data is available on serial port */

gps.encode(GPS_SoftSerial.read()); 
    /* Encode basically is used to parse the string received 
by the GPS and to store it in a buffer so that information can 
be extracted from it */ 
  } while (millis() - start < ms); 
} 
 
 void DegMinSec( double tot_val)   /* Convert data in decimal 
degrees into degrees minutes seconds form */ 
{ 
  degree = (int)tot_val; 
  minutes = tot_val - degree; 
  seconds = 60 * minutes; 
  minutes = (int)seconds; 
  mins = (int)minutes; 
  seconds = seconds - minutes; 
  seconds = 60 * seconds; 
  secs = (int)seconds; 
} 
 
 
void warn(){ 
  Serial.println(" !!!!   DANGER  !!!!! "); 
  setColor(255, 0, 0); 
  delay(250); 
  setColor(0, 0, 0); 
  delay(250); 
  } 

void safe (){ 
  setColor(0, 255, 0); 
  delay(1000); 
  setColor(0, 0, 0); 
  delay(1000); 
} 
void LatLong(){ 
        smartDelay(1000); /* Generate precise delay of 1ms */ 
        unsigned long start; 
        double lat_val, lng_val, alt_m_val; 
        uint8_t hr_val, min_val, sec_val; 
        bool loc_valid, alt_valid, time_valid; 
        lat_val = gps.location.lat(); /* Get latitude data */ 
        loc_valid = gps.location.isValid(); /* Check if valid 
location data is available */ 
 lng_val = gps.location.lng(); /* Get longtitude data 
*/ 
 
        if (!loc_valid) 
        { 
          Serial.print("Latitude : "); 
          Serial.println("*****"); 
          Serial.print("Longitude : "); 
          Serial.println("*****"); 
          setColor(0, 0, 250); 
          delay(500); 
          setColor(0, 0, 0); 
          delay(500);
	} 
        else 
        { 
          DegMinSec(lat_val); 
          Serial.print("Latitude in Decimal Degrees : "); 
          Serial.println(lat_val, 6); 
          y=lat_val; 
 
 DegMinSec(lng_val); /* Convert the decimal degree 
value into degrees minutes seconds form */          
          Serial.print("Longitude in Decimal Degrees : "); 
          Serial.println(lng_val, 6); 
          x=lng_val; 
  } 
} 
void setColor(int redValue, int greenValue, int blueValue) { 
  analogWrite(red, redValue); 
  analogWrite(green, greenValue); 
  analogWrite(blue, blueValue); 
} 
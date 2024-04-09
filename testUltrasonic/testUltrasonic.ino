#include <HX711.h>

//lib
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>          


//wifi init
char ssid[] =  "Bedroom";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Datsun5699";

//hx711 init

HX711 scale;
float calibration_factor = -48787.5 ;//-101525,-231424
float units;
float ounces;
float weight;


//ultrasonic
double duration, cm;
const int trigPin = 22;
const int echoPin = 23;


void setup() {
  Serial.begin(115200);
  delay(15);
//wifi setup
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);  
     while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
   scale.begin(4, 5);
//weight setup
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {

    getWeightReading();
    delay(10);
    getUltraReading();
    delay(10);

}


  void getWeightReading()
  {
 
unsigned long currentMillis1 = millis();
 
//  Serial.println("Reading: ");
//  Serial.print(scale.get_units(), 1);
  weight =scale.get_units(), 1;
//  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
//  delay(1000);

 }
  
 void getUltraReading()
{

pinMode(trigPin, OUTPUT); 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(6); 
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT); 
duration = pulseIn(echoPin, HIGH);
//inches = microsecondsToInches(duration); 
cm = microsecondsToCentimeters(duration);
Serial.println("ultrasonic reading ");
Serial.print(cm);
delay(100);
Serial.println("");
}

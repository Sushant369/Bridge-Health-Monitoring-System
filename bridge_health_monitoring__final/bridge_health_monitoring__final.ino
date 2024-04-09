#include <HX711.h>

//lib
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>          


//Millis
unsigned long previousMillis = 0;   
const long interval = 25000; //25 sec delay

//for 1sec
unsigned long previousMillis1 = 0;   
const long interval1 = 1000; //15 sec delay

//wifi init

char ssid[] =  "sushant";     // replace with your wifi ssid and wpa2 key
const char *pass =  "sushant3339";
String apiKey = "13GWYKQP5DZO5DHN";      //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";
            // Create an instance
WiFiClient client;

//accelerometer init 
const int x_out = A6; //D34 of ESP32
const int y_out = A3; //VN of ESP32
const int z_out = A0; //VP of ESP32
int x_adc_value, y_adc_value, z_adc_value; 



HX711 scale;
float calibration_factor = -133940 ;//-133940
float units;
float ounces;
float weight;

//ultrasonic
double duration, cm;
const int trigPin = 22;//D22 of ESP32
const int echoPin = 23;//D23 of ESP32


//Flex
const int flexPin = A4; //D32 of ESP32 
const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 3430;//4149.55; // resistance when flat
const float bendResistance =4444.44;//4444.44; //3829.79;  // resistance at 90 deg
float angle =0.00;

void setup()
{  
  
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
  pinMode(flexPin, INPUT);
   scale.begin(4, 5); //D4-dt,D5 - sk (esp32-hx711)
//weight setup
  scale.set_scale(calibration_factor);
  scale.tare();
}



void loop()
{

unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    getWeightReading();
    delay(10);
	  getAccelerometerReadings();
     
	  
//    delay(10);
	  getUltraReading();
    delay(10);
	  getFlexReading();
   delay(10);
	  uploadData();
   
  }
}

void uploadData()
{
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             
                             postStr +="&field1=";
                             postStr += String(weight);//LoadCell Value
                             Serial.print("Load cell output : ");
                             Serial.print(weight);
                             Serial.print(" KG");
                             Serial.println();

                             postStr +="&field2=";
                             postStr += String(x_adc_value);//accelerometer X
                             Serial.print("accelerometer X : ");
                             Serial.print(x_adc_value);
                                                          
                             postStr +="&field3=";
                             postStr += String(y_adc_value);//accelerometer Y
                             Serial.print(" accelerometer Y : ");
                             Serial.print(y_adc_value);
                                                                                     
                             postStr +="&field4=";
                             postStr += String(z_adc_value);//accelerometer Z
                             Serial.print(" accelerometer Z : ");
                             Serial.print(z_adc_value);
                             Serial.println();
                             
                             postStr +="&field5=";
                             postStr += String(cm);//Ultrasonic
                             Serial.print("Ultrasonic output : ");
                             Serial.print(cm);
                             Serial.print(" cm");
                             Serial.println();

                             postStr +="&field6=";
                             postStr += String(angle);//Flex
                             Serial.print("Flex output : ");
                             Serial.print(angle);
                             Serial.print("*");
                             Serial.println();

                              
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);

//                              Serial.println(String(postStr));
                                        Serial.println("Uploading...");
 
                        }
                      else
                      {
                        Serial.println("Not Uploading........");
                      }
//          client.stop();
 

  }

void getAccelerometerReadings()
{

unsigned long currentMillis1 = millis();

  if (currentMillis1 - previousMillis1 >= interval1) 
  {
    previousMillis1 = currentMillis1;
    

  x_adc_value = analogRead(x_out); /* Digital value of voltage on x_out pin */ 
  y_adc_value = analogRead(y_out); /* Digital value of voltage on y_out pin */ 
  z_adc_value = analogRead(z_out); /* Digital value of voltage on z_out pin */ 
//    Serial.println("Accelerometer readings");
//  Serial.print("x = ");
//  Serial.print(x_adc_value);
//  Serial.print("\t\t");
//  Serial.print("y = ");
//  Serial.print(y_adc_value);
//  Serial.print("\t\t");
//  Serial.print("z = ");
//  Serial.print(z_adc_value);
//  Serial.print("\t\t");
//  Serial.println("");
  //delay(100);
  

  delay(1000);
  }
}
  
  void getWeightReading()
  {
 
unsigned long currentMillis1 = millis();
 
//  Serial.println("Reading: ");
//  Serial.print(scale.get_units(), 1);
  weight =scale.get_units(), 1;
//  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
//  Serial.print(" calibration_factor: ");
//  Serial.print(calibration_factor);
//  Serial.println();
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
//  Serial.println("ultrasonic reading ");
//    Serial.print(cm);
delay(100);
//Serial.println("");
}

double microsecondsToCentimeters(double microseconds)
{return microseconds / 29 / 2;} 


//Flex sensor

 void getFlexReading()
{
//   // Read the ADC, and calculate voltage and resistance from it
  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 4095.0;
 float Rflex = R_DIV * (VCC / Vflex - 1.0);
  Serial.println("flex reading ->");
  Serial.print("Resistance: " + String(Rflex) + " ohms");

  // Use the calculated resistance to estimate the sensor's bend angle:
 float angleTemp = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  if(angleTemp>=0 && angleTemp<=90)
  {  
    angle=angleTemp;
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
  delay(500);
  }
  else
  {
    if(angleTemp<0)
    {
      angle=0;
//      Serial.println("Bend: 0 degrees");
//  Serial.println();
  delay(500);
      } 
      if(angleTemp>90)
    {
      angle=90;
//      Serial.println("Bend: 90 degrees");
//  Serial.println();
  delay(500);
      }
    } 
}
  
  

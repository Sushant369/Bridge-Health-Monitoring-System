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

char ssid[] =  "sushant";     // replace with your wifi ssid and wpa2 key
const char *pass =  "sushant3339";

HX711 scale;
float calibration_factor = -133940 ;//-101525,-231424
float units;
float ounces;
float weight;

String apiKey = "13GWYKQP5DZO5DHN";    
const char* server = "api.thingspeak.com";

WiFiClient client;

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
unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    getWeightReading();
    delay(10);
//    getAccelerometerReadings();
//     
//    
////    delay(10);
//    getUltraReading();
//    delay(10);
//    getFlexReading();
//   delay(10);
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
//
//                             postStr +="&field2=";
//                             postStr += String(x_adc_value);//accelerometer X
//                             Serial.print("accelerometer X : ");
//                             Serial.print(x_adc_value);
//                                                          
//                             postStr +="&field3=";
//                             postStr += String(y_adc_value);//accelerometer Y
//                             Serial.print(" accelerometer Y : ");
//                             Serial.print(y_adc_value);
//                                                                                     
//                             postStr +="&field4=";
//                             postStr += String(z_adc_value);//accelerometer Z
//                             Serial.print(" accelerometer Z : ");
//                             Serial.print(z_adc_value);
//                             Serial.println();
//                             
//                             postStr +="&field5=";
//                             postStr += String(cm);//Ultrasonic
//                             Serial.print("Ultrasonic output : ");
//                             Serial.print(cm);
//                             Serial.print(" cm");
//                             Serial.println();
//
//                             postStr +="&field6=";
//                             postStr += String(angle);//Flex
//                             Serial.print("Flex output : ");
//                             Serial.print(angle);
//                             Serial.print("*");
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


  void getWeightReading()
  {
 
unsigned long currentMillis1 = millis();
   weight =scale.get_units(), 1;

if (weight<0)
{
  weight=0.00;
}
else
{
  weight =scale.get_units(), 1;
}
 }

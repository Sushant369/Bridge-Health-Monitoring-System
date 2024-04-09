//
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiServer.h>    
//
//WiFiClient client;
//
//
//char ssid[] =  "Bedroom";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "Datsun5699";
//const char* server = "api.thingspeak.com";
//void setup()
//{ 
////  ESP.restart(); 
//  Serial.begin(115200);
//    delay(15); 
//    
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, pass);  
//
//        while (WiFi.status() != WL_CONNECTED) 
//     {
//            delay(500);
//            Serial.print(".");
//     }
//      Serial.println("");
//      Serial.println("WiFi connected");
//
//}
//
//void loop()
//{
//
//if (client.connect(server,80))
//{
//  Serial.println("Inside server");
//
//}
//}

//////////////////////////////reset wifi settings///////////////////////////////
void setup()
{
Serial.begin(115200);
Serial.println("Restarting in 10 seconds");
delay(10000);
ESP.restart();
}
 
void loop()
{
}

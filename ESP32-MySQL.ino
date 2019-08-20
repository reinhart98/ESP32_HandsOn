#include <WiFi.h>
#include <HTTPClient.h> 

const char *ssid =  "ssid";     // replace with your wifi ssid and wpa2 key
const char *pass =  "password";

const int lm35 = 34; //di nodeMCU D8

void setup() {
      Serial.begin(9600);
      delay(10);
      pinMode(lm35, INPUT);            
      Serial.println("Connecting to ");
      Serial.println(ssid); 
 
      WiFi.begin(ssid, pass); 
      while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected"); 
}

void loop() {  
  float intensity = analogRead(lm35);
   intensity = map(intensity, 0, 4095, 2, 150);
//  HTTP 
  HTTPClient http;    //Declare object of class HTTPClient
  String Link;
  
  Link =  "http://192.168.43.87/read_sensorlm35/add.php?temp="+String(intensity);  //path to your .php file that will send to your MySQL
  http.begin(Link);     //Specify request destination  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload   //payload ini isinya adalah isi database yang di ECHO pada file PHP
  //Serial.println("httpCode adalah" +httpCode);   //Print HTTP return code
  Serial.println(intensity);    //Print request response payload  

 http.end();  //Close connection
 delay(1000);
  
}

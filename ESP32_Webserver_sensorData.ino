#include <WiFi.h>
#include <WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "ssid"; // Enter SSID here
const char* password = "password"; //Enter Password here

WebServer server(80);

// LM35 Sensor
uint8_t LM35 = 34; //use pin with ADC 1 for wifi comunication with sensors in ESP32

float Temperature;

void setup() {
Serial.begin(9600);
delay(100);
pinMode(LM35, INPUT);
Serial.println("Connecting to ");
Serial.println(ssid);
//connect to your local wi-fi network
WiFi.begin(ssid, password);
//check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected..!");
Serial.print("Got IP: "); Serial.println(WiFi.localIP());
server.on("/", handle_OnConnect);
server.onNotFound(handle_NotFound);
server.begin();
Serial.println("HTTP server started");
}
void loop() {
server.handleClient();
}

void handle_OnConnect() {
Temperature = analogRead(LM35); // Gets the values of the temperature
Temperature = map(Temperature,0,4095,2,150);
Serial.print(Temperature);
server.send(200, "text/html", SendHTML(Temperature));
}

void handle_NotFound() {
server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat) {
String ptr = "<!DOCTYPE html> <html>\n";
ptr += "<head><meta http-equiv=\"refresh\" content=\"6\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
ptr += "<title>ESP32 Weather Report</title>\n";
ptr += "<style>html { Helvetica; display: inline-block; 0px auto; text-align: center;}\n";
ptr += "body{ 50px;} h1 {color: #444444; 50px auto 30px;}\n";
ptr += "p { 24px;color: #444444; 10px;}\n";
ptr += "</style>\n";
ptr += "</head>\n";
ptr += "<body>\n";
ptr += "<div id=\"webpage\">\n";
ptr += "<h1>ESP32 Weather Report</h1>\n";

ptr += "<p>Temperature: ";
ptr += (int)Temperaturestat;
ptr += "^C</p>";

ptr += "</div>\n";
ptr += "</body>\n";
ptr += "</html>\n";
return ptr;
}

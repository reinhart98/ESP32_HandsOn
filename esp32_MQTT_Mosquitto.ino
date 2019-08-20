#include <WiFi.h>
#include <PubSubClient.h>
// Replace the next variables with your SSID/Password combination
const char* ssid = "SSID name";
const char* password = "password";

// Add your MQTT Broker IP address, example:

const char* mqtt_server = "your mqtt broker/mosquitto IP";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//uncomment the following lines if you're using SPI
/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

float temperature = 0;


// LED Pin
const int ledPin = 2;

// LM35 Pin
const int lm35Pin = 34;
const int ldrPin = 32;

void setup() {
  Serial.begin(115200);
  // default settings

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(lm35Pin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 100) {
    lastMsg = now;
    
    // Temperature in Celsius
    temperature = analogRead(lm35Pin);   
    temperature = map(temperature,0,4095,2,150);

    float ldr = analogRead(ldrPin);

    

    char tempString[8];
    char tempStringLDR[8];
    dtostrf(temperature, 1, 2, tempString);
    dtostrf(ldr, 1, 2, tempStringLDR);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("esp32/temperature", tempString);
    client.publish("esp32/ldr", tempStringLDR);
    delay(1000);
  }
}

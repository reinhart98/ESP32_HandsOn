#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient   wifiClient;
PubSubClient client(wifiClient);

// your network information
const char *ssid     = "ssid";
const char *password = "password";

// get this information from the website
char device[] = "device token thingsboard";
char token[]  = "token thingsboard";
char server[] = "demo.thingsboard.io";

bool thingsboard_Publish(String data) {
  if (!client.connected())
  {
    while (!client.connect(device, token, NULL))
    {
      delay(100);
    }
  }

  String payload = data;
  char   attributes[100];
  payload.toCharArray(attributes, 100);
  client.publish("v1/devices/me/telemetry", attributes);
}

void thingsboard_Init() {
  if (strcmp(WiFi.SSID().c_str(), ssid) != 0)
  {
    WiFi.begin(ssid, password);
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  client.setServer(server, 1883);
}

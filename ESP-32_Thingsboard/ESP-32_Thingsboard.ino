#include "ThingsBoard.h"

const int potentioPin = 32;
const int ldrPin = 32;
const int lm35Pin = 34;

int potentioValue;
float ldrValue;
int lm35Value;

void setup()
{
  thingsboard_Init();
  Serial.begin(115200);
}

void loop()
{
  String data;
  const size_t bufferSize = JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.createObject();
  potentioValue = analogRead(potentioPin);
  ldrValue = analogRead(ldrPin);
  lm35Value = analogRead (lm35Pin);
  float lm35_suhu = map(lm35Value, 0, 4095, 2, 150);

//  Serial.println(ldrValue);
  
  
  root["potent_value "] = String(potentioValue);
  root["Intensitas "] = String(ldrValue);
  root["TEMP(^C) "]  = String(lm35_suhu);

  root.printTo(data);
  thingsboard_Publish(data);
  client.loop();
}

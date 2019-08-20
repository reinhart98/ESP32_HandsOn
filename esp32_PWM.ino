#define led_pin 15

#define freq 5000
#define channel 0
#define resolution 8
void setup() {
  // put your setup code here, to run once:
  ledcSetup(channel,freq,resolution);
  ledcAttachPin(led_pin, channel);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int dutyC=0;dutyC<=255;dutyC++){
    ledcWrite(channel,dutyC);
    delay(15);
    }

   for(int dutyC=255;dutyC>=0;dutyC--){
    ledcWrite(channel,dutyC);
    delay(15);
    }

}

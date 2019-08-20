#include <BluetoothSerial.h>

//ini CLASIC BLUETETOOH jg
jg sih sebenarnya, nama file salah xD

BluetoothSerial eps_bt;
#define eks_pinled 18
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start Serial monitor in 9600
  eps_bt.begin("ESP32_LED_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  pinMode (LED_BUILTIN, OUTPUT);//Specify that LED pin is output
  pinMode (eks_pinled, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (eps_bt.available()) //Check if we receive anything from Bluetooth
  {
    int incoming = eps_bt.read(); //Read what we recevive
    Serial.print("Received:"); Serial.println(incoming);
    if (incoming == 49)
        {
        digitalWrite(LED_BUILTIN, HIGH);
        eps_bt.println("LED turned ON");
        }
       
    if (incoming == 48)
       {
        digitalWrite(LED_BUILTIN, LOW);
        eps_bt.println("LED turned OFF");
       }
    if (incoming == 97){
        digitalWrite(eks_pinled, HIGH);
      }
    if (incoming == 100){
        digitalWrite(eks_pinled, LOW);
      }
  }

  

}

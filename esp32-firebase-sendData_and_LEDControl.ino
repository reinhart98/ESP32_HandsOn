#include <WiFi.h>                                                // esp32 library
#include <IOXhop_FirebaseESP32.h>                               // firebase library

#define FIREBASE_HOST "digitalent-kominfo-4e704.firebaseio.com"    // the project name address from firebase id
#define FIREBASE_AUTH "nq2RNcS67XVseRFd7gmnCT5yIXTrEGOHlZAPVtKz"   // the secret key generated from firebase
#define WIFI_SSID "ssid"                                          // input your home or public wifi name
#define WIFI_PASSWORD "password"                                    //password of wifi ssid

String fireStatus = "";       // led status received from firebase

int led = 2;
const int ldr = 34;
//float temperature = 0;

void setup() {

  Serial.begin(9600);

  delay(1000);

  pinMode(2, OUTPUT);
  pinMode(34, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                                                      //print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

  Firebase.setString("LED_STATUS", "OFF");                                          //send initial string of led status
  Firebase.setString("SUHU", "SUHU");

}

void loop() {
  int inten = analogRead(ldr);
  temperature = map(temperature, 0, 4095, 2, 150);
  Firebase.setInt("kelompok5-6", inten);                          //send data LDR to Firebase
  Serial.println(inten);
  fireStatus = Firebase.getString("kelompok1-2");                     // get led status input from firebase
  
  if (fireStatus == "ON") {                         // compare the input of led status received from firebase

    Serial.println("Led Turned ON");

    digitalWrite(led, HIGH);                                                         // make output led ON

  }

  else if (fireStatus == "OFF") {              // compare the input of led status received from firebase

    Serial.println("Led Turned OFF");

    digitalWrite(led, LOW);                                                         // make output led OFF

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

}

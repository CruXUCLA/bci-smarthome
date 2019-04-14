#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "cruxdemo-ff359.firebaseio.com"
#define FIREBASE_AUTH "kwzhEiKL8LwBj17vLZGcmn01PvqLWOyO80HFFOBM"
#define WIFI_SSID "Samsung Galaxy S9+_6807"
#define WIFI_PASSWORD "cruxucla"

#define path "/light1/OnOff"

const int LED = 12; // Pin D6

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  bool lightStatus = Firebase.getBool(path);
  if (lightStatus)
  {
    digitalWrite(LED, HIGH);
    Serial.println("LED On");
  }
  else
  {
    digitalWrite(LED, LOW); 
    Serial.println("LED Off");
  }
}

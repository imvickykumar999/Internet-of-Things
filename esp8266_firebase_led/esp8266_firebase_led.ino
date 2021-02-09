#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <Servo.h> 

int servoPin = 2; 
Servo Servo1; 

#define WIFI_SSID "Galaxy A21s80C5"
#define WIFI_PASSWORD "oye vicks"

#define FIREBASE_HOST "led-blink-wifi-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "VvFhb5Ij53hPmECwjzf3lxmtXXUA7a0SqW34CNSa"

FirebaseData firebaseData;

void setup() {
  Servo1.attach(servoPin); 
  
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
}

void loop() {
  
    if (Firebase.getInt(firebaseData,"/led1"))
    {
      int val2 = (firebaseData.intData());
      
      if (0<=val2<=180)
      {
        Servo1.write(val2); 
        delay(1000);
      }
      
      else{
        Serial.println("enter valid position");
      }
    }
        
    delay(200);
  // put your main code here, to run repeatedly:
}

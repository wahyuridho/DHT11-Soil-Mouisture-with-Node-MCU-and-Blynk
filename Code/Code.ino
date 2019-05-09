#include "DHTesp.h"
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
float h,t;
const int sensorPin = 4; 
int sensorState = 0;
int lastState = 0;

char auth[] = "3d46063845de45a8aeea088b3a852b65";  // Put your Auth Token here. (see Step 3 above)
char ssid[] = "vivo 1802";
char pass[] = "123456789";
DHTesp dht;
SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass); //insert here your SSID and password
  dht.setup(2, DHTesp::DHT11); // Connect DHT sensor to D4
  timer.setInterval(1000L, sendUPtime);
  pinMode(sensorPin, INPUT);
}
void sendUPtime(){
  h = dht.getHumidity();
  t = dht.getTemperature();
  
  Blynk.virtualWrite(10, t); // virtual pin 
  Blynk.virtualWrite(11, h); // virtual pin 
}
void loop()
{
  Blynk.run();
  timer.run();
  soil();
}

void soil(){
sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  String k = "Water your plants";
  Blynk.virtualWrite(9, k);
  lastState = 1;
  delay(1000);
//send notification
    
  } 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  String k = "has not been watered yet";
  Blynk.virtualWrite(9, k);
  delay(1000);
  }
  else {
    //st
    String k = "does not need water";
    Blynk.virtualWrite(9, k);
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}


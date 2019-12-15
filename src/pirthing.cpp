#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// put the WIFI credentials in wificreds.h, in the same directory as pirthing.cpp (this file) with the lines:
// const char* ssid = "WIFI SSID";
// const char* password = "WIFI SECRET PASSWORD";
// (uncommented, of course)
#include "wificreds.h"

const char* host = "max.kenkl.org";
const unsigned int clienttimeout = 60000;  //ms for client timeout in the doThing* action
#define pLED 13 //Pilot light for the PIR, in case it doesn't have its own LED
#define pIR 16 // the PIR itself - active HIGH. 16 is the only place that PULLDOWN works
#define ledDelay 33000 // ms, of course - how long does the nightlight stay on after PIR trigger?
unsigned long nowcount, delaycount; // tracking time for non-blocking delays
const char* urlon = "/lights/pirthing1_on.php"; 
const char* urloff = "/lights/pirthing1_off.php"; 
bool iState = false; // tracking whether the light is on 

void doThing(const char* url);
void hueON(void);
void hueOFF(void);

void setup() {
  pinMode(pIR, INPUT_PULLDOWN_16); // internal PULLDOWN only works on GPIO16
  pinMode(pLED, OUTPUT);

  Serial.begin(9600);

// We start by connecting to a WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

/* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
   would try to act as both a client and an access-point and could cause
   network-issues with your other WiFi-devices on your WiFi-network. */
WiFi.mode(WIFI_STA);
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

void loop() {
   nowcount = millis();

  // if the pIR sensor has tripped, update delaycount accordingly.  
  if(digitalRead(pIR) == HIGH) {
    delaycount = nowcount + ledDelay ;
    digitalWrite(pLED, HIGH);  //optional, depending on whether the PIR already has an LED,
  }
  else digitalWrite(pLED, LOW);
  
  // now, check that delaycount has not yet been reached and turn on/off
  // the red LEDs accordingly.
  
  if(millis() <= delaycount) {
    hueON();
  }
  else {
    hueOFF();
  }
}
void hueON(void) {
  if(iState == true) return; // we're already on; don't need to do anything here
  doThing(urlon);
  iState = true;
}

void hueOFF(void) {
  if(iState == false) return; // we're already off; don't need to do anything here. when does this happen?
  doThing(urloff);
  iState = false;
}
void doThing(const char* url) {

  Serial.println("Got to doThing...");
  Serial.print("connecting to ");
  Serial.println(host);

// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
  Serial.println("connection failed");
  return;
}

Serial.print("Requesting URL: ");
Serial.println(url);

// This will send the request to the server
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available() == 0) {
  if (millis() - timeout > clienttimeout) {
    Serial.println(">>> Client Timeout !");
    client.stop();
    return;
  }
}

  Serial.println("closing connection");
  Serial.println();

}

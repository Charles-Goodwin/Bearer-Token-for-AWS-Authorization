/**
   Example sketch to illustrate the provisioning of a valid bearer token from AWS
   Author Charles Goodwin Date: 1 May 2020

   IMPORTANT: Make sure you amend the following constants MY_SSID, MY_PASSWORD and MY_CREDENTIALS
   before uploading the script
   
   The Token object ensures a valid beaer token is provided on request. It only fetches a new
   bearer token from AWS when the old one has expired (usually after 1 hour)

   This script was tested on a ESP32 DevKitC board   

*/

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <WiFiClientSecure.h>

#include <token.h>

//Probably best at some point to put this in a seperate secrets header file
#define MY_SSID "***Change to your SSID ***"
#define MY_PASSWORD "*** Change to your WiFi password ***"
//credentials are accepted as a stringified JSON format
//replace anything prefixed with 'Change to your . .' to your specific credentials   
#define MY_CREDENTIALS "{\"AuthParameters\" : {\"USERNAME\" : \"Change to your user name"\", \"PASSWORD\" : \"Change to your password\"}, \"AuthFlow\" : \"USER_PASSWORD_AUTH\", \"ClientId\" : \"Change to your Client ID\"}"

WiFiMulti WiFiMulti;

// Instantiate the object, token with my credentials
Token token(MY_CREDENTIALS);

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP( MY_SSID, MY_PASSWORD);

  // wait for WiFi connection
  Serial.print("Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

}

void loop() {

  String bearerToken = token.bearer();
  Serial.print("Bearer Token: ");
  Serial.println(bearerToken);

  
  
  Serial.println();
  Serial.println("Waiting 10s before the next round...");
  delay(10000);
}

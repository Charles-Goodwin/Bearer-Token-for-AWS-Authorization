/*
  Token.cpp - Library for maintaining valid bearer Token.
  Created by Charles Goodwin, 30 April 2020.
  
*/

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>


#include "token.h"

Token::Token(String credentials) {
  _credentials = credentials;
  _expiryDate = 0;
  _bearer = "";
}

String Token::bearer(){
  Serial.begin(115200);
  _getToken = true;
  
  if(_bearer=="" || _expiryDate==0) { 
    Serial.println("Token or expiry date are missing");
  }
  else {
    if (_expiryDate <= millis()) {
        Serial.println("Token has expired");
    }
    else {
      _getToken = false;
      Serial.println("Token and expiry date are all good");
      return _bearer;
    }
  }

  if(_getToken) {
    WiFiClientSecure *_client = new WiFiClientSecure;
    if(_client) {
      {
        // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
        HTTPClient https;
        
        Serial.print("[HTTPS] begin fetching the token...\n");
        
          //if (https.begin(*_client, "https://postman-echo.com/post")) {  // HTTPS
          if (https.begin(*_client, BEARER_URL)) {  // HTTPS
          //Add Auth headers
          https.addHeader(TARGET_HEADER, TARGET_VALUE);
          https.addHeader(CONTENT_HEADER, CONTENT_VALUE);
     
          Serial.print("[HTTPS] POST...\n");
          // start connection and send HTTP header
          _httpCode = https.POST(_credentials);
    
          // httpCode will be negative on error
          if (_httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTPS] POST... code: %d\n", _httpCode);
    
            // file found at server
            if (_httpCode == HTTP_CODE_OK) {
              _expiryDate = millis() + 3500000; //Just shy of an hour into the future
              _payload = https.getString();
              _startInd = _payload.indexOf("IdToken")+10;
              _bearer = "bearer " + _payload.substring(_startInd, _startInd+973);
              Serial.println(_payload);
              Serial.println(_bearer);
              return _bearer;
            } 
          } else {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(_httpCode).c_str());
          }
    
          https.end();
        } else {
          Serial.printf("[HTTPS] Unable to connect\n");
        }
  
        // End extra scoping block
      }
    
      delete _client;
      
    } else {
      Serial.println("Unable to create client");
    }

    
  }
  
}



/*
void checkToken(void) {
  Serial.begin(115200);
  byte getToken = true;
  if(token=="" || expiryTime==0) { 
    Serial.println("Token or expiry date are missing");
  }
  else {
    if (expiryTime <= millis()) {
        Serial.println("Token has expired");
    }
    else {
      getToken = false;
      Serial.println("Token and expiry date are all good");
    }
  }

  if(getToken) {
    WiFiClientSecure *client = new WiFiClientSecure;
    if(client) {
      {
        // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
        HTTPClient https;
        
        Serial.print("[HTTPS] begin fetching the token...\n");
        
          //if (https.begin(*client, "https://postman-echo.com/post")) {  // HTTPS
          if (https.begin(*client, "https://cognito-idp.eu-west-2.amazonaws.com/")) {  // HTTPS
          //Add Auth headers
          https.addHeader("X-Amz-Target", "AWSCognitoIdentityProviderService.InitiateAuth");
          https.addHeader("Content-Type", "application/x-amz-json-1.1");

          //Set up JSON data
          String httpRequestData = MY_CREDENTIALS;  
          
          Serial.print("[HTTPS] POST...\n");
          // start connection and send HTTP header
          int httpCode = https.POST(httpRequestData);
    
          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
    
            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
              expiryTime = millis() + 3500000;
              String payload = https.getString();
              unsigned long int startInd = payload.indexOf("IdToken")+10;
              token = payload.substring(startInd, startInd+973);
              Serial.println(payload);
              Serial.println(token);
            }
          } else {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
          }
    
          https.end();
        } else {
          Serial.printf("[HTTPS] Unable to connect\n");
        }
  
        // End extra scoping block
      }
    
      delete client;
    } else {
      Serial.println("Unable to create client");
    }

    
  }
}
*/

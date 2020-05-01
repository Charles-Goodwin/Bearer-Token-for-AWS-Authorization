/*
 * Token.h - library for managing tokens
 * Created by Charles Goodwin 30 May 2020
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

#define HTTP_CODE_OK 200
#define BEARER_URL "https://cognito-idp.eu-west-2.amazonaws.com/"
#define TARGET_HEADER "X-Amz-Target"
#define TARGET_VALUE "AWSCognitoIdentityProviderService.InitiateAuth"
#define CONTENT_HEADER "Content-Type"
#define CONTENT_VALUE "application/x-amz-json-1.1"


class Token
{
  public:
    Token(String credentials);
    String bearer();
    
  private:
    unsigned long int _expiryDate;
    unsigned long int _startInd;
    String _bearer;
    bool _getToken;
    String _payload;
   // WiFiClientSecure *_client;
    int _httpCode;
    String _credentials;
};

//String token; 
//unsigned long expiryTime;

void checkToken(); 
#endif

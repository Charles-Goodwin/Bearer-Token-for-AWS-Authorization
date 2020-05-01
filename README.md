# Automate AWS Bearer Token Husbandry
Automates having a valid bearer token from the AWS Cognito Identity Provider Service  
Tested and used on an EPS32 DevKitC board

This library uses the AWS Cognito Identity Provider Service to ensure you always have a valid bearer token  
The bearer token gives you authentication to access APIs hosted on AWS  

To quickly bring you up to speed, 
1. load up the example sketch, 
2. Customise the three defined constants to your settings
3. Upload to your ESP32 and
4. watch on the serial monitor how a valid bearer token is always on hand  

Now you have just what you need to place in your Authorization Header whenever you make an AWS API request

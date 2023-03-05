#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

#define switch_1 21
#define switch_2 22
#define switch_3 23


bool trueorfalse [8][3]={
  {false,false,false},
  {false,false,true},
  {false,true,false},
  {false,true,true},
  {true,false,false},
  {true,false,true},
  {true,true,false},
  {true,true,true}
};

void setup() {
  Serial.begin(9600);
	
  WiFi.begin(WIFI_SSID, WIFI_PASS);

 pinMode(switch_1, OUTPUT);
  pinMode(switch_2, OUTPUT);
  pinMode(switch_3, OUTPUT);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED)
 {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if(WiFi.status()== WL_CONNECTED){

    HTTPClient http;
    http.begin(endpoint);

    for(int i=0; i<8; i++){

      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-API-KEY","Viola#3584");

      StaticJsonDocument<72> doc;
      String httpRequestData;

      digitalWrite(switch_1,trueorfalse[i][0]);
      digitalWrite(switch_2,trueorfalse[i][1]);
      digitalWrite(switch_3,trueorfalse[i][2]);


      doc["light_switch_1"] = trueorfalse[i][0];
      doc["light_switch_2"] = trueorfalse[i][1];
      doc["light_switch_3"] = trueorfalse[i][2];

      serializeJson(doc, httpRequestData);

      int httpResponseCode = http.PUT(httpRequestData);
      String http_response;

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      http_response = http.getString();
      Serial.println(http_response);
  
      http.end();

      delay(2000);

    }
    
  }
  else {
    Serial.println("WiFi Disconnected");}
}
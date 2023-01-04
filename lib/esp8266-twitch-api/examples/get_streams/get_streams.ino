#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include <sstream>
#include <string>
#include <cstring>
#include "credentials.h"
#include <Authorization.h>
#include <TwitchAPI.h>
#include <Networking.h>

const char* ssid = WIFIID;
const char* password = WIFIPASS;

void setup() {  
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);    
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {  
  WiFiClientSecure client;
  client.setInsecure();
  
  int connStatus = connect(client, OAUTH_HOST);
  if(connStatus == FAILED) {
    delay(5000);
    return;
  }

  string authRequest = getAuthorizationRequest(string(CLIENTID), string(CLIENTSECRET));
  client.print(authRequest.data());
  
  waitForResponse(client);

  JSONVar json = JSON.parse(processResponse(client).data());
  string accessToken = string(json["access_token"]);
  Serial.println(accessToken.data());

  connStatus = connect(client, TWITCH_API_HOST);
  if(connStatus == FAILED) {
    delay(5000);
    return;
  }

  string streamerName = "LIRIK";
  string streamerRequest = getStreams(streamerName, CLIENTID, accessToken);
  Serial.println(streamerName.data());
  client.println(streamerRequest.data());

  waitForResponse(client);
  
  JSONVar jsonResponse = JSON.parse(processResponse(client).data());
  JSONVar jsonStreammer = jsonResponse["data"][0];

  if(jsonStreammer == null) {
    Serial.println("Not live yet!");
    return;
  }

  Serial.print("id: ");
  Serial.println(jsonStreammer["id"]);
  Serial.print("user_login: ");
  Serial.println(jsonStreammer["user_login"]);
  Serial.print("user_name: ");
  Serial.println(jsonStreammer["user_name"]);
  Serial.print("game_id: ");
  Serial.println(jsonStreammer["game_id"]);
  Serial.print("game_name: ");
  Serial.println(jsonStreammer["game_name"]);
  Serial.print("type: ");
  Serial.println(jsonStreammer["type"]);
  Serial.print("title: ");
  Serial.println(jsonStreammer["title"]);
  Serial.print("viewer_count: ");
  Serial.println(jsonStreammer["viewer_count"]);
  Serial.print("started_at: ");
  Serial.println(jsonStreammer["started_at"]);
  Serial.print("language: ");
  Serial.println(jsonStreammer["language"]);
  Serial.print("thumbnail_url: ");
  Serial.println(jsonStreammer["thumbnail_url"]); 
  Serial.println("List of tags:");
  JSONVar listOfTags = jsonStreammer["tag_ids"];
  for (size_t i = 0; i < listOfTags.length(); i++) {
    Serial.print(String(i) + ": ");
    Serial.println(listOfTags[i]);
  }
  Serial.print("is_mature: ");
  Serial.println(jsonStreammer["is_mature"]);  

  Serial.println("closing connection");
  client.stop();
  Serial.println("wait 10 sec...");
  delay(10000);
}

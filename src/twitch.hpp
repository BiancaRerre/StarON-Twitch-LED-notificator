#if !defined(TWITCH_HPP__)
#define TWITCH_HPP__
#include <Arduino_JSON.h>
#ifndef ESP32
#include <ESP8266WiFi.h>
#else 
#include <WiFi.h>
#endif 
#include <WiFiClientSecure.h>

#include "./credencials.h"

WiFiClientSecure client;
// twitch connection
const char* host = "id.twitch.tv";
const uint16_t port = 443;
String access_token = "";

uint32_t lasTimeGetToken = 0;
uint32_t latTimeGetStreamerOn = 0;
bool isStreamerOn = false;

bool awaitTimeOut(WiFiClientSecure* client) {
    // read back one line from server
    // Serial.println("receiving from remote server");
    delay(500);
    unsigned long timeout = millis();
    while (client->available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client->stop();
            return 1;
        }
    }
    return 0;
}

bool handGetTwitchToken() {
    client.stop();
    client.setInsecure();

    delay(100);

    if (!client.connect(host, port)) {
        Serial.println("1 connection failed");
        Serial.println("wait 5 sec...");
        lasTimeGetToken = millis();
        return false;
    }

    String data = "client_id=" + clientId + "&client_secret=" + clientSecret +
                  "&grant_type=client_credentials";

    //   This will send the request to the server
    client.println("POST /oauth2/token HTTP/1.1");
    client.println("Host: id.twitch.tv");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(data.length()));
    client.println();
    client.println(data);

    Serial.println("send get Token");

    if (awaitTimeOut(&client)) return false;


    std::stringstream ss;
    bool capturing = false;
    while (client.available()) {
        char ch = static_cast<char>(client.read());
        if (ch == '{' || capturing == true || ch == '}') {
            capturing = true;
            ss << ch;
            if (ch == '}') {
                capturing = false;
            }
        }
    }

    JSONVar json = JSON.parse(ss.str().c_str());

    access_token = String((const char*)json["access_token"]);
    Serial.println(access_token);
    client.stop();
    return true;
}

bool getTwitchToken() {
    if (!WiFi.isConnected()) return 0;
    if (lasTimeGetToken != 0 &&
        (millis() - lasTimeGetToken) < (access_token == "" ? 3000 : 60000)) {
        return access_token != "";
    }

    if (!handGetTwitchToken()) {
        access_token = "";
    }
    lasTimeGetToken = millis();
    return access_token != "";
}

bool handStreamerIsOn(String streamerName) {
    client.stop();
    client.setInsecure();
    delay(100);

    if (!client.connect("api.twitch.tv", port)) {
        Serial.println("2 connection failed");
        Serial.println("wait 5 sec...");
      
        return false;
    }

    Serial.println("GET /helix/streams?user_login=" + streamerName +
                   "HTTP/1.1");
    // This will send the request to the server
    client.println("GET /helix/streams?user_login=" + streamerName +
                   " HTTP/1.1");
    client.println("Host: api.twitch.tv");
    client.println("Authorization: Bearer " + access_token);
    client.println("Client-Id: " + clientId);
    client.println();
    client.println();

    if (awaitTimeOut(&client)) return 0;

    bool capturing = false;
    String response = "";
    while (client.available()) {
        char ch = static_cast<char>(client.read());
        if (ch == '{' || capturing == true || ch == '}') {
            capturing = true;
            response.concat(ch);
            if (ch == '}') {
                capturing = false;
            }
        }
    }
    Serial.println(response);//
    Serial.println(response.length());//
    return response.length() > 100;
    response = "";    
}

bool streamerIsOn(String streamerName) {
    if (getTwitchToken()) {
        if ((millis() - latTimeGetStreamerOn) < 3000) return isStreamerOn;
        isStreamerOn = handStreamerIsOn(streamerName);
        
        latTimeGetStreamerOn = millis();
        return isStreamerOn;
    }
    return false;
}

#endif  // TWITCH_HPP__

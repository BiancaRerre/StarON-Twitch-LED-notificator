#include <Adafruit_NeoPixel.h>
#ifdef ESP32
#include <ESPmDNS.h>
#include <WebServer.h>
#else
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

#include <cstring>
#include <sstream>
#include <string>

#include "./HTML.h"
#include "./twitch.hpp"

// LED config
#define PIN 4
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// WifiManager config
void wmConfig() {
    // WiFiManager, Local intialization. Once its business is done, there is no
    // need to keep it around
    WiFiManager wm;
    // wm.resetSettings(); // reset the wifi config

    bool res;
    res = wm.autoConnect("StarON");  // password protected ap

    if (!res) {
        // Serial.println("Failed to connect");
        //  ESP.restart();
    } else {
        // if you get here you have connected to the WiFi
        // Serial.println("connected...yeey :)");
    }
    // Serial.println(WiFi.localIP());
}

// WebServer config
#ifdef ESP32
WebServer server(80);  // Set web server port number to 80
#else
ESP8266WebServer server(80);  // Set web server port number to 80
#endif
String streamerName = "";
String cor = "";

void hendleIndex() {                           // send HTML to the page
    server.send(200, "text/html", postForms);  // check HTML.h file
}

void handleGetParam() {
    if (server.hasArg("STREAMER")) {
        streamerName = server.arg("STREAMER");  // get the streamer name and put
                                                // on the streamerName variable
    }
    if (server.hasArg("COLOR")) {
        cor = server.arg("COLOR");  // get the COLOR
    }

    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, atol(cor.c_str()));
        pixels.show();
        delay(200);
        pixels.clear();
        pixels.show();
        delay(200);
    }

    // Serial.println("Streamer Name - ");
    // Serial.print(streamerName);
    Serial.print("cor:  ");
    Serial.println(cor);
}

void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    wmConfig();
    if (!MDNS.begin("starOn")) {  // Start the mDNS responder for esp8266.local
        Serial.println("Error setting up MDNS responder!");
    }
    // Serial.println("mDNS responder started");
    MDNS.addService("http", "tcp", 80);
    WiFi.hostname("starOn");

    server.on("/", hendleIndex);
    server.on("/getName", handleGetParam);
    server.onNotFound(handleNotFound);
    server.begin();
    // Serial.println("HTTP server started");

    // LED

    pixels.begin();
    pixels.clear();
}

uint32_t lasTimeUpdateLed;

void loop() {
#ifndef ESP32
    MDNS.update();
#endif

    server.handleClient();

    if (streamerName != "" && (millis() - lasTimeUpdateLed) > 300) {
        // Serial.println("Recebendo stream data");
        // Serial.println(response);
        if (streamerIsOn(streamerName)) {
            pixels.setPixelColor(0, atol(cor.c_str()));
            pixels.show();
            Serial.println("TA ON");
        } else {
            pixels.clear();
            pixels.show();
            Serial.println("TA OFF");
        }
        lasTimeUpdateLed = millis();
        // Serial.println("wait 5 sec...");
        // delay(5000);
    }
}
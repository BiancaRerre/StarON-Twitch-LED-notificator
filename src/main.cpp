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
#include "./style.h"
#include "./js.h"
#include "./twitch.hpp"

// LED config
#define PIN 4
#define NUMPIXELS 4
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int status = 0;


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
int corR = 0;
int corG = 0;
int corB = 0;

void hendleIndex() {                           // send HTML to the page
    Serial.println("GET /");
    server.send(200, "text/html", postForms);  // check HTML.h file
}

void handleStyle() {                           // send HTML to the page
    Serial.println("GET /style.css");
    server.send(200, "text/css", style);  // check HTML.h file
}

void handlejs() {                           // send HTML to the page
    Serial.println("GET /js");
    server.send(200, "application/javascript", js);  // check HTML.h file
}


void handleStatus() {                           // send JSON to the page
//jsonstatus = "[{\"canal\":\""+streamerName+"\",\"color\":\""+cor+"\",\"status\":\""+status+"\"}]";   
    Serial.println("GET /staus");
    server.send(200, "application/json", "[{\"canal\":\""+streamerName+"\",\"color\":\""+cor+"\",\"status\":\""+status+"\"}]"); 
}


void handleGetParam() {

    if (server.hasArg("STREAMER")) {
        streamerName = server.arg("STREAMER");  // get the streamer name and put
                                                // on the streamerName variable
    }
    if (server.hasArg("COLOR")) {
        cor = server.arg("COLOR");  // get the COLOR
        cor = "0x"+cor;}
    if (server.hasArg("cor")) {
        cor = server.arg("cor");  // get the COLOR
    }
    pixels.fill(pixels.Color(100,100,100),0);
    Serial.println("GET /getname");
    Serial.print("Streamer: ");
    Serial.print(streamerName);


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
    server.send(200, "text/html", message);  // check HTML.h file
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
    server.on("/getname", handleGetParam);
    server.on("/style.css", handleStyle);
    server.on("/status", handleStatus);
    server.on("/js", handlejs);
    server.onNotFound(handleNotFound);
    server.begin();
    // Serial.println("HTTP server started");

    // LED

    pixels.begin();
    pixels.clear();
    pixels.show();
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
            pixels.setPixelColor(1, atol(cor.c_str()));
            pixels.show();
            server.handleClient();
            pixels.setPixelColor(0, corR, corG, corB); //definir cor dos leds
            pixels.show(); //aplicar alterações nos leds
            Serial.println("TA ON");
            status = 1;
        } else {
            server.handleClient();
            pixels.clear();//definir que quer apagar leds
            pixels.show(); //aplicar alterações nos leds
            Serial.println("TA OFF");
            status = 0;
        }
        lasTimeUpdateLed = millis();
        // Serial.println("wait 5 sec...");
        // delay(5000);
    }
 
}

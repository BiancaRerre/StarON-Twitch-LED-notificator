#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>   
#include <sstream>
#include <string>
#include <cstring>
#include "credencials.h"
#include "HTML.h"



// twitch connection
const char* host = "id.twitch.tv";
const uint16_t port = 443;
String access_token = "";


//LED config
#define PIN 4
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// WifiManager config
void wmConfig(){
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
   // wm.resetSettings(); // reset the wifi config
    
    bool res;
    res = wm.autoConnect("StarON"); // password protected ap
 
    if(!res) {
        //Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
       // Serial.println("connected...yeey :)");
    }
       // Serial.println(WiFi.localIP());
}

// WebServer config
ESP8266WebServer server(80); // Set web server port number to 80
String streamerName="";
String cor ="";

void hendleIndex() {  // send HTML to the page
    server.send(200, "text/html", postForms); // check HTML.h file
}

void handleGetParam() {

    if (server.hasArg("STREAMER")) {
        streamerName = server.arg("STREAMER"); // get the streamer name and put on the streamerName variable
    }
    if (server.hasArg("COLOR")) {
        cor = server.arg("COLOR"); // get the COLOR
    }

    for(int i = 0 ; i < 3; i++){

      pixels.setPixelColor(0,atol(cor.c_str()));
      pixels.show();
      delay(200);
      pixels.clear();
      pixels.show();
      delay(200);
    }

    //Serial.println("Streamer Name - ");
    //Serial.print(streamerName);
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
     if (!MDNS.begin("starOn")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
    }
   //Serial.println("mDNS responder started");
   MDNS.addService("http", "tcp", 80);
   MDNS.notifyAPChange();
   WiFi.hostname("starOn");

    server.on("/", hendleIndex);
    server.on("/getName", handleGetParam);
    server.onNotFound(handleNotFound);
    server.begin();
    //Serial.println("HTTP server started");

    //LED
 
    pixels.begin();
    pixels.clear();

}

 
void loop() {
  MDNS.update();
  
  WiFiClientSecure client;
  server.handleClient();
  client.setInsecure();

  if(streamerName != ""){

  if (!client.connect(host, port)) {
    Serial.println("1 connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }  

  String data = "client_id=" + clientId + "&client_secret=" + clientSecret + "&grant_type=client_credentials";
  
//   This will send the request to the server
  client.println("POST /oauth2/token HTTP/1.1");
  client.println("Host: id.twitch.tv");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.println("Content-Length: " + String(data.length()));
  client.println();
  client.println(data);


  //read back one line from server
 // Serial.println("receiving from remote server");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  std::stringstream ss;
  bool capturing = false;
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    if(ch == '{' || capturing == true || ch == '}') {
      capturing = true;
      ss << ch;
      if(ch == '}') {
        capturing = false;
      }
    }    
  }  

  JSONVar json = JSON.parse(ss.str().c_str());  

  access_token = String((const char*) json["access_token"]);
  Serial.println(access_token);
  
  if (!client.connect("api.twitch.tv", port)) {
    Serial.println("2 connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }  

  //Serial.println("GET /helix/streams?user_login="+streamerName+ " HTTP/1.1");
  // This will send the request to the server
  client.println("GET /helix/streams?user_login="+streamerName+ " HTTP/1.1");
  client.println("Host: api.twitch.tv"); 
  client.println("Authorization: Bearer " + access_token);
  client.println("Client-Id: " + clientId);
  client.println();
  client.println();

  timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 10000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }
  ss.clear();
  delay(1000);

  capturing = false;
  String response = "";
  while (client.available()) {    
    char ch = static_cast<char>(client.read());
    if(ch == '{' || capturing == true || ch == '}') {
      capturing = true;
      response.concat(ch);
      if(ch == '}') {
        capturing = false;
      }
    }
  }

 // Serial.println("Recebendo stream data");
 // Serial.println(response);
  if (response.length() > 27){
    pixels.setPixelColor(0,atol(cor.c_str()));
    pixels.show();   
    Serial.println("TA ON");
  }else{
     pixels.clear();
     pixels.show(); 
    Serial.println("TA OFF");
    
  }



  Serial.println("closing connection");
  client.stop();

  Serial.println("wait 5 sec...");
  delay(5000);
  }
  }
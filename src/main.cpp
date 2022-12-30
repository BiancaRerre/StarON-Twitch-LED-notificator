#include <Adafruit_NeoPixel.h>
#ifdef ESP32
#include <ESPmDNS.h>
#include <WebServer.h>
#else
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#define EEPROM_SIZE 512
int metaAddress = 0;
int metaLenght = 4;
int jsonAddress = 4;

#include <Preferences.h>
#include <string.h>
char* clientIdRead; // Declaração do ponteiro global
char* clientSecretRead; // Declaração do ponteiro global
String clientSecret;
String clientId;

#include "./credencials.h"
#include "./credenciaisHTML.h"

String EEPROM_read(int index, int length) {
    String text = "";
    char ch = 1;

    for (int i = index; (i < (index + length)) && ch; ++i) {
        if (ch = EEPROM.read(i)) {
            text.concat(ch);
        }
    }
    return text;
}

int EEPROM_write(int index, String text) {
    for (int i = index; i < text.length() + index; ++i) {
        EEPROM.write(i, text[i - index]);
    }
    EEPROM.write(index + text.length(), 0);
    EEPROM.commit();
    Serial.println("alterações foram salvas na memoria!");

    return text.length() + 1;
}

void pulsar();

DynamicJsonDocument getEEPROM_JSON() {
    String jsonRead =
        EEPROM_read(jsonAddress, EEPROM_read(metaAddress, metaLenght).toInt());

    Serial.print("Dados salvos: ");
    Serial.print("Streamer: "+String(readData("STREAMER")));
    Serial.print(" RGB("+String(readData("R"))+",");
   Serial.print( String(readData("G"))+","+String(readData("B"))+") cor: #"+String(readData("cor")));

    DynamicJsonDocument jsonDoc(EEPROM_SIZE);

    deserializeJson(jsonDoc, jsonRead);

    return jsonDoc;
}

void setEEPROM_JSON(DynamicJsonDocument jsonDoc) {
    String jsonWriteString;

    serializeJson(jsonDoc, jsonWriteString);

    Serial.print("JSON Write: ");
    Serial.println(jsonWriteString);

    EEPROM_write(metaAddress,
                 (String)EEPROM_write(jsonAddress, jsonWriteString));
}

#include <cstring>
#include <sstream>
#include <string>

#include "./HTML.h"
#include "./js.h"
#include "./style.h"
#include "./twitch.hpp"

// LED config
#ifdef ESP32
#define LED_R D12
#define LED_G D2
#define LED_B D4
#else
#define LED_R 14
#define LED_B 13
#define LED_G 12
#define GND D0
#endif
#define PIN 4
#define NUMPIXELS 1
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
        Serial.println("not connected...");
        delay(150);
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    } else {
        // if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
    }
    Serial.println(WiFi.localIP());
}

// WebServer config
#ifdef ESP32
WebServer server(80);  // Set web server port number to 80
#else
ESP8266WebServer server(80);  // Set web server port number to 80
#endif
String streamerName = "";
String cor = "";
String userName = "null";
int corR = 0;
int corG = 0;
int corB = 0;
int modo = 0;



void handleStyle() {  // send HTML to the page
    Serial.println("GET /style.css");
    server.send(200, "text/css", style);  // check HTML.h file
}

void handlejs() {  // send HTML to the page
    Serial.println("GET /js");
    server.send(200, "application/javascript", js);  // check HTML.h file
}

void handleStatus() {  // send JSON to the page
                       // jsonstatus =
    // "[{\"canal\":\""+streamerName+"\",\"color\":\""+cor+"\",\"status\":\""+status+"\"}]";
    Serial.println("GET /staus");
    DynamicJsonDocument jsonDoc = getEEPROM_JSON();
    const char *readcanal = jsonDoc["canal"];
    const char *readcor = jsonDoc["cor"];
    // int r = jsonDoc["rgb"][0];
    // int g = jsonDoc["rgb"][1];
    // int b = jsonDoc["rgb"][2];
if(streamerName.equalsIgnoreCase(userName)){
    server.send(200, "application/json",
                "[{\"canal\":\"" +String(readData("STREAMER"))+ "\",\"color\":\"" +
                    String(readData("cor")) + "\",\"status\":\"" + status + "\"}]");
}
else{
    server.send(200, "application/json",
                "[{\"canal\":\"" + String(readData("STREAMER")) + "\",\"color\":\"" +
                    String(readData("cor")) + "\",\"status\":\"" + status + "\"}]");

}

}

void handleGetParam() {
    if (server.hasArg("STREAMER")) {
      if(!server.arg("STREAMER").equalsIgnoreCase(streamerName)){
        streamerName = server.arg("STREAMER");  // get the streamer name and put
                                                // on the streamerName variable
        
        saveData("STREAMER",server.arg("STREAMER").c_str());
        Serial.print(" Salvando nome "); 
    }                       
    }
    if (server.hasArg("cor")) {
        
        if(!server.arg("cor").equalsIgnoreCase(cor)){
        cor = server.arg("cor");  // get the COLOR
        saveData("cor",server.arg("cor").c_str());
        Serial.print(" Salvando cor "); 
    }       

    }

    if (server.hasArg("r")) {
      if(corR != server.arg("r").toInt()){
        const char* CR = server.arg("r").c_str();
        corR = server.arg("r").toInt();  // get the COLOR
        Serial.print(" Salvando R: "+corR);
   
        saveData("R",CR);
       // Serial.print(" Salvando R "); 
        }
    }
    if (server.hasArg("g")) {
           if(corR != server.arg("g").toInt()){
        const char* CG = server.arg("g").c_str();
        corG = server.arg("g").toInt();  // get the COLOR
        Serial.print(" Salvando G: "+corG);
        saveData("G",CG);
       // Serial.print(" Salvando R "); 
        }
    }

    if (server.hasArg("b")) {
          if(corB != server.arg("b").toInt()){
        const char* CB = server.arg("b").c_str();
        corB = server.arg("b").toInt();  // get the COLOR
        Serial.print(" Salvando B: "+corB);
        saveData("B",CB);
       // Serial.print(" Salvando R "); 
        }
    }



    if (server.hasArg("clientId")) {
        clientId = server.arg("clientId");  // get the streamer name and put
                                                // on the streamerName variable
        
        saveDataString("clientId",String(server.arg("clientId")));
        Serial.print(" Salvando clientId "); 
                           
    }

        if (server.hasArg("clientSecret")) {
        clientSecret = server.arg("clientSecret");  // get the streamer name and put
                                                    // on the streamerName variable
        
        saveDataString("clientSecret",String(server.arg("clientSecret")));
        Serial.print(" Salvando clientSecret "); 
                           
    }


 


    for (int i = 0; i < 3; i++) {  // piscar 3 vezes mostrando a cor escolhida

        server.handleClient();
        analogWrite(LED_R, corR);
        analogWrite(LED_G, corG);
        analogWrite(LED_B, corB);
        pixels.setPixelColor(0, corR, corG, corB);
        pixels.show();
        delay(200);

        server.handleClient();
        analogWrite(LED_R, 0);
        analogWrite(LED_G, 0);
        analogWrite(LED_B, 0);
        pixels.clear();
        pixels.show();
        delay(200);
    }

 //   Serial.println("GET /getname");
    Serial.print("Streamer: ");
    Serial.print(streamerName);
    Serial.print(" - ");
    Serial.println("color: " + cor + " rgb(" + server.arg("r") + ", " +
                 server.arg("g") + ", " + server.arg("b")+")");
    Serial.println(") COR: #"+ String(readData("cor")));
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

void updateStreamerStatus() {
    if (getTwitchToken() && handStreamerIsOn(streamerName.c_str())) {
        isStreamerOn = true;
    } else {
        isStreamerOn = false;
    }
}

void setup() {

 
  //clientId, clientSecret


#ifdef ESP8266
    // se for esp8266, definir a frequencia do pwm em "mais de 8mil" hertz (isso
    // ajuda a não flikar na camera) essa opção é mais pra quem for usar o
    // staron com led rgb não endereçável, ou ligar ele numa fita não
    // endereçável
    analogWriteFreq(8001);
#endif

    EEPROM.begin(EEPROM_SIZE);
    DynamicJsonDocument jsonDoc(EEPROM_SIZE);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(GND, OUTPUT);
    digitalWrite(GND, 0);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(150);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(150);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(150);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(150);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(150);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(150);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

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
    server.on("/credencial", handlecredenciais);
    server.onNotFound(handleNotFound);
    server.begin();
    // Serial.println("HTTP server started");

    // LED

    pixels.begin();
    pixels.clear();

    jsonDoc = getEEPROM_JSON();
    streamerName = String(readData("STREAMER"));;
    cor = String(readData("cor"));
   char* corRchar = readData("R");
   char* corGchar = readData("G");
   char* corBchar = readData("B");
   char* modochar = readData("modo");

  corR = String(corRchar).toInt();
  corG = String(corGchar).toInt();
  corB = String(corBchar).toInt();
  modo = String(modochar).toInt();


//saveData("clientId","");
delay(10);
//saveData("clientSecret","");
}

uint32_t lasTimeUpdateLed;
uint32_t piscante = 0;

uint32_t lastTimeUdpdatePrintHeap = 0;
void loop() {
    // Serial.print("testando");

  if ((millis() - lastTimeUdpdatePrintHeap) > 400) {
    Serial.print("Heap: ");
    Serial.println(ESP.getFreeHeap());
    lastTimeUdpdatePrintHeap = millis();
  }

#ifndef ESP32
    MDNS.update();
#endif

    server.handleClient();

    if (streamerName != "" && (millis() - lasTimeUpdateLed) > 500) {
        // Serial.println("Recebendo stream data");
        // Serial.println(response);
        if (streamerIsOn(streamerName)) {
            server.handleClient();

            analogWrite(LED_R, corR);
            analogWrite(LED_G, corG);
            analogWrite(LED_B, corB);
            digitalWrite(GND, 0);

            pixels.setPixelColor(0, corR, corG, corB);  // definir cor dos leds
            pixels.show();  // aplicar alterações nos leds
            Serial.println("TA ON");
            status = 1;
            digitalWrite(LED_BUILTIN, 0);
        } else {
            analogWrite(LED_R, 0);
            analogWrite(LED_G, 0);
            analogWrite(LED_B, 0);
            digitalWrite(GND, 0);
            server.handleClient();
            pixels.clear();  // definir que quer apagar leds
            pixels.show();   // aplicar alterações nos leds
            Serial.println("TA OFF");
            status = 0;
            digitalWrite(LED_BUILTIN, 1);
        }
        lasTimeUpdateLed = millis();
        // Serial.println("wait 5 sec...");
        // delay(5000);
    }
    if (streamerName == "") {
        pulsar();
    }

}

const int LED_PIN = LED_BUILTIN;  // LED DO ESP para feedback
const int PERIODO = 1000;         // período em milissegundos
int contador = 0;                 // contador para o software timer
int intensidade = 0;              // intensidade do sinal PWM
int direcao = 1;                  // direção do aumento da intensidade

void pulsar() {
    // altera a intensidade do sinal PWM de acordo com o software timer
    if (contador == 0) {
        // se o contador estiver zerado, inicia o aumento da intensidade
        intensidade = 0;
        direcao = 1;
    } else if (contador == PERIODO / 2) {
        // se o contador atingir metade do período, inicia a diminuição da
        // intensidade
        direcao = -1;
    } else if (contador == PERIODO || intensidade == 0) {
        // se o contador atingir o período ou a intensidade chegar a zero,
        // reseta o contador e a direção
        contador = 0;
        direcao = 1;
    }
    // aplica a intensidade atual ao sinal PWM
    analogWrite(LED_R, corR);
    analogWrite(LED_G, corG);
    analogWrite(LED_B, corB);
    analogWrite(GND, intensidade);
    analogWrite(LED_PIN, intensidade);
    intensidade += direcao;  // incrementa ou decrementa a intensidade
    contador++;              // incrementa o contador
    delay(4);  // espera por 4 milissegundo antes de continuar o loop
}


void corrigirnome(){

}

void saveData(const char* name, const char* value) {
  Preferences preferences;
  preferences.begin("StarOn", false);
  preferences.putString(name, value);
  preferences.end(); // Gravar os dados na memória flash de forma permanente
}

void saveDataString(const char* name, String value) {
  Preferences preferences;
  preferences.begin("StarOn", false);
  preferences.putString(name, value);
  preferences.end(); // Gravar os dados na memória flash de forma permanente
}

char* readData(const char* name) {
  static char value[32];
  Preferences preferences;
  preferences.begin("StarOn", false);
  strlcpy(value, preferences.getString(name).c_str(), sizeof(value));
  preferences.end();
  return value;
}


void hendleIndex() {  // send HTML to the page
    Preferences preferences;
    preferences.begin("StarOn", false);
    Serial.println("GET /");
    Serial.println(preferences.getString("clientId", ""));
    if (preferences.getString("clientId", "") != "") {//verifica se tem credenciais
  // o valor está salvo
  Serial.println("clientID está salvo: " + preferences.getString("clientID", ""));
 server.send(200, "text/html", postForms);  // se tiver, levar pra página principal} else {
  // o valor não está salvo
  }else{
  Serial.println("clientID não está salvo");
     // server.send(200, "text/html", credenciais);  // se não tiver salvo,  levar pra pagina de cadastrodas credenciais
handlecredenciais();
}
 preferences.end();
}



void handlecredenciais() {  // send HTML to the page
    
    Serial.println("GET /credenciais");
      server.send(200, "text/html", credenciais);  // se não tiver salvo,  levar pra pagina de cadastrodas credenciais
    if (server.hasArg("clientId")) {
        clientId = server.arg("clientId");  // get the streamer name and put
                                                // on the streamerName variable
        
        saveDataString("clientId",String(server.arg("clientId")));
        Serial.print(" Salvando clientId "); 
                           
    }

        if (server.hasArg("clientSecret")) {
        clientSecret = server.arg("clientSecret");  // get the streamer name and put
                                                    // on the streamerName variable
        
        saveDataString("clientSecret",String(server.arg("clientSecret")));
        Serial.print(" Salvando clientSecret "); 
                           
    }

}



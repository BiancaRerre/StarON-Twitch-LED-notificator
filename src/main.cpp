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
int slot;

#include <Preferences.h>
#include <string.h>
char* clientIdRead; // Declaração do ponteiro global
char* clientSecretRead; // Declaração do ponteiro global
String clientSecret;
String clientId;

//#include "./credencials.h"
#include "./credenciaisHTML.h"

char* readData(const char* name);
void handlecredenciais();

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
    Serial.print("Streamer: "+String(readData("STREAMER1")));
    Serial.print(" RGB("+String(readData("R1"))+",");
   Serial.println( String(readData("G1"))+","+String(readData("B1"))+") cor: #"+String(readData("cor1")));

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
#define GND 16
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
int modo = 3; //0: led do esp, 1:led rgb comum, 2:led endereçável, 3:todos.



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
                "[{\"canal\":\"" +String(readData("STREAMER1"))+ "\",\"color\":\"" +
                    String(readData("cor1")) + "\",\"status\":\"" + status + "\"}]");
}
else{
    server.send(200, "application/json",
                "[{\"canal\":\"" + String(readData("STREAMER1")) + "\",\"color\":\"" +
                    String(readData("cor1")) + "\",\"status\":\"" + status + "\"}]");

}

}

void handleGetParam() {
    if (server.hasArg("STREAMER")) {
   //   if(!server.arg("STREAMER").equalsIgnoreCase(streamerName)){
        streamerName = server.arg("STREAMER");  // get the streamer name and put
                                                // on the streamerName variable
        if(server.arg("slot") == "1"){
        saveData("STREAMER1",server.arg("STREAMER").c_str());
        }
        if(server.arg("slot") == "2"){
        saveData("STREAMER2",server.arg("STREAMER").c_str());
        }
        if(server.arg("slot") == "3"){
        saveData("STREAMER3",server.arg("STREAMER").c_str());
        }
        if(server.arg("slot") == "4"){
        saveData("STREAMER4",server.arg("STREAMER").c_str());
        }



        Serial.print(" Salvando nome "); 
    //}                       
    }
    if (server.hasArg("cor")) { //salvando a cor em hexa
        
    //    if(!server.arg("cor").equalsIgnoreCase(cor)){
        cor = server.arg("cor");  // get the COLOR

        if(server.arg("slot") == "1"){
        saveData("cor1",server.arg("cor").c_str());
        }
        if(server.arg("slot") == "2"){
        saveData("cor2",server.arg("cor").c_str());
        }
        if(server.arg("slot") == "3"){
        saveData("cor3",server.arg("cor").c_str());
        }
        if(server.arg("slot") == "4"){
        saveData("cor4",server.arg("cor").c_str());
        }
        Serial.print(" Salvando cor "); 
   // }       

    }

    //salvando a cor em rgb
    if (server.hasArg("r")) {
        if(corR != server.arg("r").toInt()){
        const char* CR = server.arg("r").c_str();
        corR = server.arg("r").toInt();  // get the COLOR
        Serial.print(" Salvando R: "+corR);

       if(server.arg("slot") == "1"){
        saveData("R1",CR);
       }
       if(server.arg("slot") == "2"){
        saveData("R2",CR);
       }
       if(server.arg("slot") == "3"){
        saveData("R3",CR);
       }
       if(server.arg("slot") == "4"){
        saveData("R4",CR);
       }

       // Serial.print(" Salvando R "); 
        }
    }
    if (server.hasArg("g")) {
           if(corR != server.arg("g").toInt()){
        const char* CG = server.arg("g").c_str();
        corG = server.arg("g").toInt();  // get the COLOR
        Serial.print(" Salvando G: "+corG);

       if(server.arg("slot") == "1"){
        saveData("G1",CG);
       }
       if(server.arg("slot") == "2"){
        saveData("G2",CG);
       }
       if(server.arg("slot") == "3"){
        saveData("G3",CG);
       }
       if(server.arg("slot") == "4"){
        saveData("G4",CG);
       }
        
       // Serial.print(" Salvando R "); 
        }
    }

    if (server.hasArg("b")) {
          if(corB != server.arg("b").toInt()){
        const char* CB = server.arg("b").c_str();
        corB = server.arg("b").toInt();  // get the COLOR
        Serial.print(" Salvando B: "+corB);

      if(server.arg("slot") == "1"){
        saveData("B1",CB);
       }
      if(server.arg("slot") == "2"){
        saveData("B2",CB);
       }
      if(server.arg("slot") == "3"){
        saveData("B3",CB);
       }
      if(server.arg("slot") == "4"){
        saveData("B4",CB);
       }
        
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
    Serial.println(") COR: #"+ String(readData("cor1")));
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

  // jsonDoc = getEEPROM_JSON();
    streamerName = String(readData("STREAMER1"));;
    cor = String(readData("cor1"));
   char* corRchar = readData("R1");
   char* corGchar = readData("G1");
   char* corBchar = readData("B1");
   char* modochar = readData("modo");

   Serial.print("cores salvas rgb: "+ String(readData("R1"))+" "+ String(readData("G1"))+" "+ String(readData("B1")));
   Serial.println();
  

  corR = String(corRchar).toInt();
  corG = String(corGchar).toInt();
  corB = String(corBchar).toInt();
  modo = String(modochar).toInt();
  Serial.println("cor salva:");
  Serial.println(corR);
  Serial.println(corG);
  Serial.println(corB);
  Serial.println("");
  Serial.println(modo);


//saveData("clientId","");
delay(10);
//saveData("clientSecret","");
}

uint32_t lasTimeUpdateLed;
uint32_t piscante = 0;

uint32_t lastTimeUdpdatePrintHeap = 0;
void loop() {
    // Serial.print("testando");

  if ((millis() - lastTimeUdpdatePrintHeap) > 13000) {
    Serial.print("Heap: ");
    Serial.println(ESP.getFreeHeap());
    lastTimeUdpdatePrintHeap = millis();
  }

#ifndef ESP32
    MDNS.update();
#endif

    server.handleClient();

    if (streamerName != "" && (millis() - lasTimeUpdateLed) > 500) {


//implementando sistema de slots, pra 4 streamers
        
        slot++;
        if(slot == 5){
          slot = 0;
        }








        if (streamerIsOn(streamerName)) {// SE O STREAMER  ESTIVER EM LIVE

        
            server.handleClient();


         ligarled(String(readData("R1")).toInt(),String(readData("G1")).toInt(),String(readData("B1")).toInt());

            Serial.println("TA ON");
          //  Serial.println(String(readData("R1")).toInt());
          //  Serial.println(String(readData("G1")).toInt());
          //  Serial.println(String(readData("B1")).toInt());
          //  Serial.println(digitalRead(GND));
            status = 1;
            
            

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

void ligarled(int R, int G, int B){
   //  if(modo == 0 || modo == 3){
            digitalWrite(LED_BUILTIN, 1);// ACENDER O LED DO ESP 
              digitalWrite(LED_BUILTIN, 0);// ACENDER O LED DO ESP 
          //  }
          //  if(modo == 1 || modo == 3){
              analogWrite(LED_R, R);// SETAR A COR DO LED RGB COMUM
              analogWrite(LED_G, G);// SETAR A COR DO LED RGB COMUM
              analogWrite(LED_B, B);// SETAR A COR DO LED RGB COMUM
              digitalWrite(GND, 0);
          //  }
          //  if(modo == 2 || modo == 3){
            //SETAR A COR DO LED ENDEREÇÁVEL
            pixels.setPixelColor(0, R, G, B);  // definir cor dos leds
            pixels.show();  // aplicar alterações nos leds
          //  }
}


#include "Networking.h"

#define PORT 443

int connect(
    WiFiClientSecure &client,
    const char* host
) {    
    if (!client.connect(host, PORT)) {
        return FAILED;
    }
    return CONNECTED;
}

string processResponse(WiFiClientSecure &client) {
    stringstream response;
    bool isCapturingBody = false;
    int countingBrackets = 0;
    while (client.available()) {
        char ch = static_cast<char>(client.read());        

        if(ch == '{' || ch == '[') {
            countingBrackets++;
            isCapturingBody = true;
        }

        if(isCapturingBody) {
            response << ch << flush;
        }

        if(ch == '}' || ch == ']') {
            countingBrackets--;

            if(countingBrackets == 0) {  
                isCapturingBody = false;              
                break;
            }
        }        
    }

    return response.str();
}

void waitForResponse(WiFiClientSecure &client) {
    const unsigned long TIMEOUT_LIMIT = 5000;
    const unsigned long DELAY_TIMEOUT = 5000;
    const unsigned long DELAY_RESPONSE_OK = 1000;
    
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > TIMEOUT_LIMIT) {
            Serial.println(">>> Request timeout! <<<");
            client.stop();
            delay(DELAY_TIMEOUT);
            return;
        }    
    }
    delay(DELAY_RESPONSE_OK);
}

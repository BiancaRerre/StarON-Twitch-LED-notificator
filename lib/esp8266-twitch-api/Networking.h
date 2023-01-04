#include <WiFiClientSecure.h>
#include <sstream>
#include <string>

#define CONNECTED 1
#define FAILED    0

using namespace std;

int connect(
    WiFiClientSecure &client,
    const char* host
);

string processResponse(WiFiClientSecure &client);
void waitForResponse(WiFiClientSecure &client);

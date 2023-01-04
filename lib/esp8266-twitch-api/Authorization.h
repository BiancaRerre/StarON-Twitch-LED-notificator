#include <Arduino.h>
#include <Networking.h>
#include <string>

#define OAUTH_HOST "id.twitch.tv"

string getAuthorizationRequest(
    string clientId,
    string clientSecret
);

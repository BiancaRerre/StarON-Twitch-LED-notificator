#include <Networking.h>
#include <sstream>
#include <string>

#define TWITCH_API_HOST "api.twitch.tv"

using namespace std;

string getStreams(
    string streamerName,
    const char* clientId,
    string accessToken
);

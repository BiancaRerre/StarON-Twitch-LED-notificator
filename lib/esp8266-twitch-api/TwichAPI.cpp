#include "TwitchAPI.h"

string getStreams(
    string streamerName,
    const char* clientId,
    string accessToken
) {
    stringstream header;
    header << "GET /helix/streams?user_login=" << streamerName << " HTTP/1.1" << endl;
    header << "Host: " << TWITCH_API_HOST << endl;
    header << "Authorization: Bearer " << accessToken << endl;
    header << "Client-Id: " << clientId << endl;    
    header << endl;
    header << endl;

    return header.str();
}


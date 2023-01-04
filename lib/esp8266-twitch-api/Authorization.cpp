#include <Authorization.h>

string getAuthorizationRequest(
    string clientId,
    string clientSecret
) {
    stringstream data;
    data << "client_id=" << clientId << flush;
    data << "&client_secret=" << clientSecret << flush;
    data << "&grant_type=client_credentials" << flush;
    string body = data.str();

    stringstream header;
    header << "POST /oauth2/token HTTP/1.1" << endl;
    header << "Host: " << OAUTH_HOST << endl;
    header << "Content-Type: application/x-www-form-urlencoded" << endl;

    header << "Content-Length: " << body.size() << endl;
    header << endl;
    header << body << endl;

    return header.str();
}

# ESP8266 Twitch Api
Twitch API to be used with ESP8266 boards

If you wan to run the tests, create a file named `credentials.h` inside the example folder with the following template:
```
#define WIFIID       "YOUR WIFI NETWORK HERE"
#define WIFIPASS     "YOUR WIFI PASSWORD HERE"
#define CLIENTID     "APPLICATION'S CLIENT ID HERE"
#define CLIENTSECRET "APPLICATION'S CLIENT SECRET HERE"
```

## FAQ

**Problem:** My ESP8266 is not connecting to the WIFI  
**Solution:** Check if you are trying to connect to a 5GHz wifi network. If this is your case, try to connect to a 2.4GHz instead.

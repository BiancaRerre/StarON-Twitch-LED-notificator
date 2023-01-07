<html lang="en">

# StarON ⭐

StarON is a LED cube project that lights up when a Twitch streamer is online. It was built for ESP8266 and ESP32 and can be powered via USB. When first plugged in, StarON will ask for a "Client ID" and "Client Secret" from the Twitch API, which you can get by creating a new application on the [Twitch Developers Console](https://dev.twitch.tv/console/apps/create).

StarON also has a MDNS hostname, which is "staron.local". This means you can access the StarON web page by typing "http://staron.local" into your browser, instead of having to figure out the IP address of the board.

## Installation

1. Download the StarON binary from the [latest release](https://github.com/BiancaRerre/StarON-Twitch-LED-notificator/releases/tag/staron) or clone the repository using the "Clone or download" button on GitHub.
2. Connect your ESP8266 or ESP32 to your computer using a USB cable.
3. Open the [https://web.esphome.io/](https://web.esphome.io/) website and follow the instructions to flash the binary to the board using `esptool`.

## Configuration

To configure StarON, just access the StarON web page in your browser. You can find the IP address of your board in the Arduino IDE's serial output, or using a network scanner. If you are using the MDNS hostname, simply type "http://staron.local" into your browser.

On the web page, just type in the name of the Twitch streamer you wish to follow and choose a color for the RGB LED. StarON will light up whenever the streamer is online.

## Contribution

If you would like to contribute to the StarON project, simply create a new "Pull request" with your changes. All contributions are welcome and will be reviewed by the project maintainers.

## Credits

- Thanks to the ChatGPT virtual assistant [ChatGPT](https://chat.openai.com/chat) for helping in creating this `README.md`.

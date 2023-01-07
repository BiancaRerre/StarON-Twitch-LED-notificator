<html lang="es">


# StarON ⭐

StarON es un proyecto de LED que se enciende cuando un streamer de Twitch está en línea. Fue creado para ESP8266 y ESP32 y se puede alimentar a través de USB. Cuando se conecta por primera vez, StarON le pedirá un "Client ID" y un "Client Secret" de la API de Twitch, que puede obtenerse creando una nueva aplicación en la [Consola de Desarrolladores de Twitch](https://dev.twitch.tv/console/apps/create).

StarON también tiene un nombre de host MDNS, que es "staron.local". Esto significa que puede acceder a la página web de StarON escribiendo "http://staron.local" en su navegador, en lugar de tener que descubrir la dirección IP de la placa.

## Instalación

1. Descargue el binario de StarON en la [última versión](https://github.com/BiancaRerre/StarON-Twitch-LED-notificator/releases/tag/staron) o clonando el repositorio usando el botón "Clone or download" en GitHub.
2. Conecta tu ESP8266 o ESP32 a tu computadora usando un cable USB.
3. Abra el sitio [https://web.esphome.io/](https://web.esphome.io/) y siga las instrucciones para grabar el binario en la placa usando `esptool`.

## Configuración

Para configurar StarON, simplemente acceda a la página web de StarON en su navegador. Puede encontrar la dirección IP de su placa en la salida serial del Arduino IDE o usando un escáner de red. Si está usando el nombre de host MDNS, simplemente escriba "http://staron.local" en su navegador.

En la página web, simplemente escriba el nombre del streamer de Twitch que desea seguir y elija un color para el LED RGB. StarON se encenderá siempre que el streamer esté en línea.

## Contribución

Si desea contribuir al proyecto StarON, simplemente cree un nuevo "Pull request" con sus cambios. Todas las contribuciones son bienvenidas y serán evaluadas por los mantenedores del proyecto.

## Créditos

- Gracias al asistente virtual [ChatGPT](https://chat.openai.com/chat) por ayudar a crear este `README.md`.

# StarON ⭐

StarON é um projeto de cubo LED que acende quando um streamer da Twitch está online. Ele foi criado para ESP8266 e ESP32 e pode ser alimentado via USB. Quando ligado pela primeira vez, o StarON irá solicitar um "Client ID" e "Client Secret" da API da Twitch, que você pode obter criando uma nova aplicação na [Twitch Developers Console](https://dev.twitch.tv/console/apps/create).

O StarON também possui um nome de host MDNS, que é "staron.local". Isso significa que você pode acessar a página da web do StarON digitando "http://staron.local" em seu navegador, em vez de ter que descobrir o endereço IP da placa.

## Instalação

1. Faça o download do binário do StarON na [última release](https://github.com/BiancaRerre/StarON-Twitch-LED-notificator/releases/tag/staron) ou clonando o repositório usando o botão "Clone or download" no GitHub.
2. Conecte o seu ESP8266 ou ESP32 ao computador usando um cabo USB.
3. Abra o site [https://web.esphome.io/](https://web.esphome.io/) e siga as instruções para gravar o binário na placa usando o `esptool`.

## Configuração

Para configurar o StarON, basta acessar a página da web do StarON em seu navegador. Você pode encontrar o endereço IP da sua placa na saída serial do Arduino IDE ou usando um scanner de rede. Se você estiver usando o nome de host MDNS, basta digitar "http://staron.local" em seu navegador.

Na página da web, basta digitar o nome do streamer da Twitch que você deseja seguir e escolher uma cor para o LED RGB. O StarON irá acender sempre que o streamer estiver online.

## Contribuição

Se você deseja contribuir para o projeto StarON, basta criar um novo "Pull request" com suas alterações. Todas as contribuições são bem-vindas e serão avaliadas pelos mantenedores do projeto.

## Créditos

- Obrigado ao assistente virtual [ChatGPT](https://chat.openai.com/chat) pela ajuda na criação deste `README.md`.

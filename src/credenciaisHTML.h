char credenciais[] PROGMEM = R"===(
<head>
    <title>⭐StarOn Config</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>

 <div class="quadrado">

    <style>
.instructions {
  color:white;
  position: absolute;
  background-color: rgba(0, 0, 1, 0.9);
  border-radius: 5px;
  box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.5);
  padding: 10px;
backdrop-blur: 10px;
}

a {
  color: inherit; /* herda a cor do elemento pai */
  text-decoration: none; /* remove a sublinhado */
}

body{
  color:#fff;
    background: #20293c;
    min-height: 90vh;
    display: flex;
    justify-content: center;
    align-items: center;
  }

.color-picker{
    position: relative;
}
.color-indicator{
    display: inline-block;
    width: 7em;
    height: 7em;
    border-bottom: 10px;
    background-color: #fff;
    border-radius: 10px;
    vertical-align: middle;
}
#color-picker{
  margin-top: 15px;
  display: inline-block;  
  vertical-align: middle;
  margin-left: 0px;
}

#prendecores{
  display: inline-block;  
  vertical-align: middle;
  width: 20em;
}

#rodape{
  color: #1e2737;
  
  border-bottom-left-radius: 25px;
  border-bottom-left-radius: 25px;
 
  margin-right: 20px;
text-align: right; 
transition: color 1.3s;
}

#rodape:hover{
  color: #ff00bf;
animation-duration: 1s;
}

.footer {
  position: absolute;
  right: 0;
  bottom: 0;
  left: 0;
  padding: 1rem;
  background-color: #000;
  text-align: center;
}
.footer p {
text-decoration: none;
color: #fff;
}
.footer a {
  text-decoration: none;
  color: red;
}
.footer a:hover {
  text-decoration: underline;
  color: blue;
}
h2{
   color:#ff00bf;
   text-align: center;
    align-items: center;
}
.canal, input{
   text-shadow: 0px 0px 2px #000;
   
  text-align: center;
  font-size: 20px;
   color:#ff00bf;
  background: #20293c;
  border-radius: 5px;
   border-width: thin;
   border-color: #ff00bf;
   width: 15.5em;
   height:1.6em;
  
}
.quadrado{
  padding-top: 4vh;
  padding-bottom: 1vh;
  background: #242E42;
  border-radius: 25px;

  width: 70vw;
}
.botao{
  margin-top: 5vh;
  margin-bottom: 5vh;
  font-size: 20px;
  color:#fff;
  background: #ff00bf;
  border-radius: 5px;
   border-width: 2px;
   width: 15.5em;
   height:1.6em;
   border-color: #ff00bf;

transition: box-shadow 1.1s;
}

.botao:active{
  box-shadow: 0px 0px 50px rgb(255, 000, 255);

transition: box-shadow 0.1s;
}

/*Huge thanks to @tobiasahlin at http://tobiasahlin.com/spinkit/ */
.spinner {
  margin: 0 auto 0;
  width: 70px;
  text-align: center;
}

.spinner > div {
  width: 18px;
  height: 18px;
  background-color: #ff00bf;
 
  border-radius: 100%;
  display: inline-block;
  -webkit-animation: sk-bouncedelay 1.4s infinite ease-in-out both;
  animation: sk-bouncedelay 1.4s infinite ease-in-out both;
}

.spinner .bounce1 {
  -webkit-animation-delay: -0.32s;
  animation-delay: -0.32s;
}

.spinner .bounce2 {
  -webkit-animation-delay: -0.16s;
  animation-delay: -0.16s;
}

@-webkit-keyframes sk-bouncedelay {
  0%, 80%, 100% { -webkit-transform: scale(0) }
  40% { -webkit-transform: scale(1.0) }
}

@keyframes sk-bouncedelay {
  0%, 80%, 100% { 
    -webkit-transform: scale(0);
    transform: scale(0);
  } 40% { 
    -webkit-transform: scale(1.0);
    transform: scale(1.0);
  }
}



@media only screen and (max-width: 680px) {
  .quadrado{
  padding-top: 5vh;
  padding-bottom: 5vh;
  background: #242E42;
  border-radius: 25px;
  width: 90vw;
}
#prendecores{
  display: inline-block;  
  vertical-align: middle;
  width: 9em;

}
.botao{
  margin-top: 5vh;
  margin-bottom: 5vh;
max-width: 95vw;
}
  input{
max-width: 90vw;
}
.color-indicator{
    display: inline-block;
    width: 0em;
    height: 50px;
    border-bottom: 10px;
    background-color: #fff;
    border-radius: 10px;
    vertical-align: middle;
}
#rodape{
  color: #1e2737;
 
  margin-right: 0px;
text-align: center; 
transition: color 1.3s;
}
 
}



      svg path {
        animation: rainbow 10s linear infinite;
      }

      @keyframes rainbow {
        0% {
          stroke: hsl(0, 100%, 50%);
        }
        10% {
          stroke: hsl(36, 100%, 50%);
        }
        20% {
          stroke: hsl(72, 100%, 50%);
        }
        30% {
          stroke: hsl(108, 100%, 50%);
        }
        40% {
          stroke: hsl(144, 100%, 50%);
        }
        50% {
          stroke: hsl(180, 100%, 50%);
        }
        60% {
          stroke: hsl(216, 100%, 50%);
        }
        70% {
          stroke: hsl(252, 100%, 50%);
        }
        80% {
          stroke: hsl(288, 100%, 50%);
        }
        90% {
          stroke: hsl(324, 100%, 50%);
        }
        100% {
          stroke: hsl(360, 100%, 50%);
        }
      }
    </style>
  </head>
  <body>
    <center>
  <svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="200px" height="98px" viewBox="0 0 200 98" version="1.1">
    <g id="surface1">
      <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:hsl(0, 100%, 50%);stroke-opacity:1;stroke-miterlimit:4;" d="M 456.752695 77.752551 L 153.253828 77.253189 L 119.249883 14.250319 L 90.254414 77.253189 L 24.746133 78.751276 L 74.747578 131.748406 L 48.751641 206.245855 L 122.249414 164.752551 L 199.246641 205.24713 L 168.751406 129.251594 L 219.252773 78.251913 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
      <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:hsl(0, 100%, 50%);stroke-opacity:1;stroke-miterlimit:4;" d="M 271.253906 150.751913 L 271.253906 102.748406 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
      <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:hsl(0, 100%, 50%);stroke-opacity:1;stroke-miterlimit:4;" d="M 355.250039 201.252232 L 355.749961 116.249681 L 433.247109 196.249362 L 433.247109 114.252232 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
<path style="fill:none;stroke-width:18;stroke-linecap:square;stroke-linejoin:round;stroke:${color.hexString};stroke-opacity:1;stroke-miterlimit:4;" d="M 270.504023 119.495536 C 261.329531 120.411033 252.145781 121.317283 243.498984 129.501276 C 234.852188 137.67602 226.723828 153.128508 229.501172 168.497768 C 232.278516 183.876276 245.952305 199.171556 261.496172 203.499362 C 277.049297 207.827168 294.463242 201.196747 304.498711 190.497449 C 314.543438 179.807398 317.20043 165.039222 313.497305 152.499681 C 309.79418 139.96014 299.730938 129.63074 291.500742 124.498406 C 283.270547 119.366071 276.882656 119.430804 270.504023 119.495536 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    </g>
    </svg>

<br>
<form action="/" method="post">
  <label for="client_id"><h2>Client <span id="info">ID:</span></label><br>
  <input type="text" id="client_id" name="clientId" required minlength="12" pattern="[^\s]*"></h2><br>
 
  <label for="client_secret"><h2>Secret:</label><br>
  <input type="text" id="client_secret" name="clientSecret" required minlength="12" pattern="[^\s]*"></h2><br>
  
  <button class="botao" type="submit" value="Salvar">SALVAR</button>
</form> 
<br>
<div>
  
 <script>const info = document.getElementById('info');

const instructions = {
  'pt': `Para obter o seu client_id e secret da API da Twitch, siga os seguintes passos:<br>
  1. Acesse o site da Twitch e faça login com sua conta.<br>
  2. Vá para a página de <a href='https://dev.twitch.tv/'>desenvolvedores dev.twitch.tv</a>.<br>
  3. Clique em 'Registrar sua aplicação'.<br>
  4. Preencha o formulário de registro e clique em 'Registrar'.<br>
  5. Copie o client_id e o secret exibidos na página de detalhes da sua aplicação.`,
  'en': `To get your Twitch API client_id and secret, follow these steps:<br>
  1. Go to the Twitch website and log in with your account.<br>
  2. Go to the <a href='https://dev.twitch.tv/'>developers dev.twitch.tv</a> page.<br>
  3. Click on 'Register your application'.<br>
  4. Fill out the registration form and click 'Register'.<br>
  5. Copy the client_id and secret displayed on your application's details page.`,
  'es': `Para obtener su client_id y secret de la API de Twitch, siga estos pasos:<br>
  1. Vaya al sitio web de Twitch y inicie sesión con su cuenta.<br>
  2. Vaya a la página de <a href='https://dev.twitch.tv/'>desarrolladores dev.twitch.tv</a>.<br>
  3. Haga clic en 'Registrar su aplicación'.<br>
  4. Complete el formulario de registro y haga clic en 'Registrar'.<br>
  5. Copie el client_id y el secret que aparecen en la página de detalles de su aplicación.`,
};

const instructionsElement = document.createElement('div');
instructionsElement.classList.add('instructions');
instructionsElement.style.display = 'none';
instructionsElement.addEventListener('mouseleave', function() {
  instructionsElement.style.display = 'none';
});
document.body.appendChild(instructionsElement);

info.addEventListener('mouseenter', function(event) {
  const language = navigator.language.substring(0, 2) in instructions ? navigator.language.substring(0, 2) : 'en';
  const instructionText = instructions[language];
  instructionsElement.innerHTML = instructionText;
  instructionsElement.style.top = event.clientY + 'px';
  instructionsElement.style.left = event.clientX + 'px';
  instructionsElement.style.display = 'block';
});
</script>



)===";
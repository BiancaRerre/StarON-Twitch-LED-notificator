const char postForms[] PROGMEM = R"===(
    <html lang="pt-BR">
<head> 
  <title>⭐StarOn</title>
  <link rel="icon" href="data:image/svg+xml,<svg xmlns=%22http://www.w3.org/2000/svg%22 viewBox=%220 0 100 100%22><text y=%22.9em%22 font-size=%2290%22>⭐</text></svg>">
  <link rel="stylesheet" href="style.css"> 
</head>
<style>      
body{
  color:#fff;
    background: #20293c;
    min-height: 90vh;
    display: flex;
    justify-content: center;
    align-items: center;
  }
</style>


<body>
  
   <div class="quadrado"><div>
         

  <div>
  <H1 id="logo"></h1><br>
    <h2 id="info">canal<br><h2>
    <input class="canal" id="canal" type="text" name="STREAMER">
     
      <div class="color-picker"></div>
      <input class="botao" type="submit" value="SALVAR" onclick="salvar();">
      <BR>
      
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Color Picker 1</title>
    
      
      
    <div id="prendecores">
      <div id="color-indicator" class="color-indicator"></div>
      <div id="color-picker"></div>
    </div>
 
    <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>

    <script>
      let cor ="#ffffff"// variavel color
      
        let colorIndicator = document.getElementById('color-indicator');
        const colorPicker = new iro.ColorPicker("#color-picker", {
            width:180, color: "#fff" ,layout: [{ component: iro.ui.Wheel }]
        });
        colorPicker.on('color:change', function(color) {
            colorIndicator.style.backgroundColor = color.hexString;
            cor =  color.hexString; //definir variavel color

            document.getElementById('logo').innerHTML =`<center><svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="200px" height="98px" viewBox="0 0 200 98" version="1.1">
    <g id="surface1">
    <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:${color.hexString};stroke-opacity:1;stroke-miterlimit:4;" d="M 456.752695 77.752551 L 153.253828 77.253189 L 119.249883 14.250319 L 90.254414 77.253189 L 24.746133 78.751276 L 74.747578 131.748406 L 48.751641 206.245855 L 122.249414 164.752551 L 199.246641 205.24713 L 168.751406 129.251594 L 219.252773 78.251913 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:${color.hexString};stroke-opacity:1;stroke-miterlimit:4;" d="M 271.253906 150.751913 L 271.253906 102.748406 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:${color.hexString};stroke-opacity:1;stroke-miterlimit:4;" d="M 355.250039 201.252232 L 355.749961 116.249681 L 433.247109 196.249362 L 433.247109 114.252232 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
   <path style="fill:none;stroke-width:18;stroke-linecap:square;stroke-linejoin:round;stroke:${color.hexString};stroke-opacity:1;stroke-miterlimit:4;" d="M 270.504023 119.495536 C 261.329531 120.411033 252.145781 121.317283 243.498984 129.501276 C 234.852188 137.67602 226.723828 153.128508 229.501172 168.497768 C 232.278516 183.876276 245.952305 199.171556 261.496172 203.499362 C 277.049297 207.827168 294.463242 201.196747 304.498711 190.497449 C 314.543438 179.807398 317.20043 165.039222 313.497305 152.499681 C 309.79418 139.96014 299.730938 129.63074 291.500742 124.498406 C 283.270547 119.366071 276.882656 119.430804 270.504023 119.495536 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    </g>
    </svg>`
    console.log("R:"+hexToRgb(color.hexString).r+"  "+"G:"+hexToRgb(color.hexString).g+"  "+"B:"+hexToRgb(color.hexString).b+"  "+color.hexString)
    
          
        });

        document.getElementById('logo').innerHTML =`<center><svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="200px" height="98px" viewBox="0 0 200 98" version="1.1">
    <g id="surface1">
    <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:#ff00bf;stroke-opacity:1;stroke-miterlimit:4;" d="M 456.752695 77.752551 L 153.253828 77.253189 L 119.249883 14.250319 L 90.254414 77.253189 L 24.746133 78.751276 L 74.747578 131.748406 L 48.751641 206.245855 L 122.249414 164.752551 L 199.246641 205.24713 L 168.751406 129.251594 L 219.252773 78.251913 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:#ff00bf;stroke-opacity:1;stroke-miterlimit:4;" d="M 271.253906 150.751913 L 271.253906 102.748406 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    <path style="fill:none;stroke-width:21;stroke-linecap:round;stroke-linejoin:round;stroke:#ff00bf;stroke-opacity:1;stroke-miterlimit:4;" d="M 355.250039 201.252232 L 355.749961 116.249681 L 433.247109 196.249362 L 433.247109 114.252232 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
   <path style="fill:none;stroke-width:18;stroke-linecap:square;stroke-linejoin:round;stroke:#ff00bf;stroke-opacity:1;stroke-miterlimit:4;" d="M 270.504023 119.495536 C 261.329531 120.411033 252.145781 121.317283 243.498984 129.501276 C 234.852188 137.67602 226.723828 153.128508 229.501172 168.497768 C 232.278516 183.876276 245.952305 199.171556 261.496172 203.499362 C 277.049297 207.827168 294.463242 201.196747 304.498711 190.497449 C 314.543438 179.807398 317.20043 165.039222 313.497305 152.499681 C 309.79418 139.96014 299.730938 129.63074 291.500742 124.498406 C 283.270547 119.366071 276.882656 119.430804 270.504023 119.495536 " transform="matrix(0.421941,0,0,0.422414,0,0)"/>
    </g>
    </svg>`

    function salvar(){ // ao clicar no botão de salvar 
    document.getElementById("info").innerHTML = `<div class="spinner">
  <div class="bounce1"></div>
  <div class="bounce2"></div>
  <div class="bounce3"></div>
</div>`
  
      

      var xmlhttp = new XMLHttpRequest();
             xmlhttp.open("GET", `/getname?slot=1&canal=${document.getElementById('canal').value}&STREAMER=${document.getElementById('canal').value}&cor=${cor.slice(1)}&r=${hexToRgb(cor).r}&g=${hexToRgb(cor).g}&b=${hexToRgb(cor).b}`);
             xmlhttp.send(null);
              console.log("----------------------------------------")
              console.log("Cor enviada: "+"R:"+hexToRgb(cor).r+"  "+"G:"+hexToRgb(cor).g+"  "+"B:"+hexToRgb(cor).b+cor.slice(1))
              console.log("Canal enviado: "+document.getElementById('canal').value)
              console.log("----------------------------------------")
              
         
      if (navigator.userAgent.indexOf("Firefox") != -1) { // abortar se for firefox
        setTimeout(function(){ xmlhttp.abort(); atualizar2(); }, 2000);         
      }
     
    
    }

  function hexToRgb(hex) {
  var shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i;
  hex = hex.replace(shorthandRegex, function(m, r, g, b) {
    return r + r + g + g + b + b;
  });

  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}
console.log(hexToRgb('#ff55cc'))

    </script>
   </div> </div>
   <div id="rodape">Design by <rerre>Bianca Rerre</rerre></div>
  <script type="text/javascript" src="/js"></script>
</body>
</html>

)===";

const String postForms = R"===(
  <html lang="pt-BR">
<head>
  <title>⭐StarOn</title>
</head>
<body>
  
   <div class="quadrado"><div>
         

  <div>
  <H1 id="logo"></h1><br>
    <h2>canal<h2>
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
      let cor// variavel color
      
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
                  
       console.log(color.hexString); 
          
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
      `/?STREAMER=${document.getElementById('canal').value}&COLOR=${cor.slice(1)}`
      console.log("")
      console.log(`GET /?STREAMER=${document.getElementById('canal').value}&COLOR=${cor.slice(1)}`)
      console.log("Cor enviada: "+cor.slice(1))
      console.log("Canal enviado: "+document.getElementById('canal').value)
      console.log("")

      var xmlhttp = new XMLHttpRequest();
             xmlhttp.open("GET", `/?STREAMER=${document.getElementById('canal').value}&COLOR=${cor.slice(1)}`);
             xmlhttp.send();
      
      
    }

    </script>
   </div>
</body>
</html>
    <style>
      
      
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
.canal{
   text-shadow: 0px 0px 2px #000;
   
  text-align: center;
  font-size: 20px;
   color:#ff00bf;
  background: #20293c;
  border-radius: 5px;
   border-width: thin;
   border-color: #ff00bf;
   width: 10.5em;
   height:1.6em;
  
}
.quadrado{
  padding-top: 5vh;
  padding-bottom: 5vh;
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
    width: 10.5em;
   height:1.6em;
   border-color: #ff00bf;
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
 
}
</style>
)===";

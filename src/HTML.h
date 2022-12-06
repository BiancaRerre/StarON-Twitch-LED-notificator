const String postForms = R"===(<html lang="pt-BR">
<head>
  <title>⭐on</title>
</head>
<body>
  
   <div class="quadrado"><div>
  <div>
  <H1><center>STAR ON</h1><br>
    <h2>canal<h2>
    <input class="canal" type="text" name="STREAMER">
     
      <div class="color-picker"></div>
      <input class="botao" type="submit" value="SALVAR">
      <BR>
      
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Color Picker 1</title>
    <link rel="stylesheet" href="style.css">
      
      
    <div id="prendecores">
      <div id="color-indicator" class="color-indicator"></div>
      <div id="color-picker"></div>
    </div>
 
    <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>

    <script>
      
        let colorIndicator = document.getElementById('color-indicator');
        const colorPicker = new iro.ColorPicker("#color-picker", {
            width:180, color: "#fff" ,layout: [{ component: iro.ui.Wheel }]
        });
        colorPicker.on('color:change', function(color) {
            colorIndicator.style.backgroundColor = color.hexString;
                  
       console.log(color.hexString); 
          
        });
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
    width: 9em;
    height: 50px;
    border-bottom: 10px;
    background-color: #fff;
    border-radius: 10px;
    vertical-align: middle;
}
 
}
</style>

)===";

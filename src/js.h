 char js[] PROGMEM = R"===(
 function atualizar2() {

  let xhr = new XMLHttpRequest();
  xhr.open('GET', '/status');
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');

  xhr.onprogress = function () {
    console.log("CARREGANDO");
  }


  xhr.onload = function () {
    var obj = JSON.parse(xhr.responseText);  // obj é a variavel correspondente ao xhr.responseText, 

    canal = obj[0].canal
    color = obj[0].color
    canalstatus = obj[0].status

    if (canal != "") {
      if (canalstatus == "1") {
        document.getElementById("info").innerHTML = "<b style=\"text-shadow: #" + obj[0].color + " 0px 0 5px; color: #" + obj[0].color + "; \">★ </b><i>" + obj[0].canal + "</i> - online!"
      }
      if (canalstatus == "0") {
        document.getElementById("info").innerHTML = "<b style=\"text-shadow: #" + obj[0].color + " 0px 0 5px; color: #" + obj[0].color + "; \">★ </b><i>" + obj[0].canal + "</i> - offline!"
      }
    }else{
     document.getElementById("info").innerHTML = "canal"
    }

    


    console.log(obj[0])

  }
  xhr.send();
}



setInterval("atualizar2()", 2000);
atualizar2(); //atualização inicial dos dados

)===";

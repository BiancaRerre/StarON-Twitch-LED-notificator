char style[] PROGMEM = R"===(
#check{

    display: none;

}

.barra{
width:200px;
height: 400px;
border-radius: 25px;
  padding:1px;
  
	position: absolute;

  background-color: #ff00bf;

	

	

		transition: all .2s linear;

	left: -300px;

}



nav{

	width: 200px;

	position: absolute;

	top: 60px;

}



nav a{

	text-decoration: none;

}



#icone{

	cursor: pointer;

	padding: 4px;

	position: absolute;

	z-index: ;

}



#imgmenu{

  cursor: pointer;

	padding: 10px;

	position: absolute;

	z-index: 1;

  height: 100%;

}



.link{

	background-color: #0000;

	padding: 20px;

	font-size: 12pt;

	font-family: "Arial";

	transition: all .2s linear;

	color:  #f4f4f9;

	border-bottom: 2px solid #FFFFFFCC;

}



.link:hover{

	background-color: #050542;



}



#check:checked ~ .barra{

	transform: translateX(300px);



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
    width: 10.5em;
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
)===";

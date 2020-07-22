#include "Arduino.h"

String Config_Wifi_Page = R"=====(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
  <form action="/get">
    Wifi <input type="text" name="wifiName">
    <input type="Submit" value="Next">
  </form><br>
</body>
</html>
	 )=====";

String Config_Wifi_PW_Page = R"=====(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
  <form action="/get">
    Password <input type="text" name="wifiPassword">
    <input type="Submit" value="Send">
  </form><br>
</body>
</html>
	 )=====";


String Config_Wifi_Sucess = R"=====(
<!DOCTYPE HTML><html>
<head>
<style>
     * {
        box-sizing: border-box;
       }
     html { 
        font-family: 'Open Sans', sans-serif; 
        display: block; 
        margin: 0px auto; 
        text-align: center;
        color: #333333;
        }  

     body{
        background-color: white;
        margin-top: 50px;
     }  

     h1 {
        margin: 50px auto 30px;
        }  
</style>
</head>
   <body>
  <h1> WiFi Configurado com Sucesso! </h1>
</body>
</html>
	 )=====";


String Config_Wifi_Erro = R"=====(
<!DOCTYPE HTML><html>
<head>
<style>
     * {
        box-sizing: border-box;
       }
     html { 
        font-family: 'Open Sans', sans-serif; 
        display: block; 
        margin: 0px auto; 
        text-align: center;
        color: #333333;
        }  

     body{
        background-color: white;
        margin-top: 50px;
     }  

     h1 {
        margin: 50px auto 30px;
        }  
</style>
</head>
   <body>
  <h1> Problema ao Tentar Configurar WiFi! </h1>
</body>
</html>
	 )=====";

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

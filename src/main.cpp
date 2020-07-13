/*
********************************************************************************
*  File : main.cpp
*  Brief: Web Server to Control ESP8266 reles
*
*    _____                     _             
*   |_   _|                   | |            
*     | | _ ____   _____ _ __ | |_ _   _ ___ 
*     | || '_ \ \ / / _ \ '_ \| __| | | / __|
*    _| || | | \ V /  __/ | | | |_| |_| \__ \
*    \___/_| |_|\_/ \___|_| |_|\__|\__,_|___/
*
*  Author: Marcelo S. Fassarella
*  Copyright: 2020 Inventus, All rights reserved 
*             This software component is Inventus property.      
*             You may not use this file except previously authorized by Inventus.   
********************************************************************************                                         
*/
//https://lastminuteengineers.com/esp8266-dht11-dht22-web-server-tutorial/
//https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
//https://circuits4you.com/2016/12/16/esp8266-web-server-html/
//https://randomnerdtutorials.com/esp8266-web-server-spiffs-nodemcu/


#include <Arduino.h>
#include <esp8266wifi.h>
#include <ESP8266WebServer.h>
//#include "ESPAsyncWebServer.h"
#include "index.h"
#include "notfoundpage.h"
#include "DHT.h"
#include <WiFiUdp.h>
#include "NTPClient.h"
//#include "time.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// network credentials
const char* ssid = "GVT-34C0";
const char* password = "3903000663";

// Set web server port number to 80
ESP8266WebServer  server(80);

// Date & time with NTP
const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora
const int fusoHorario = -10800;           // Fuso horário em segundos (-03h = -10800 seg)
const int taxaDeAtualizacao = 1800000;    // Taxa de atualização do servidor NTP em milisegundos
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);


// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;
const int dhtpin = D7;     // Digital pin connected to the DHT sensor

// Current time && Previous time
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


float Temperature = 25;
float Humidity = 83;

//prototypes
String SendHTML(float TempCstat,float Humiditystat);
void handle_OnConnect();
void handle_NotFound();
String getDiaHora(void);

// functions
// Initialize DHT sensor.
DHT dht(dhtpin, DHTTYPE);                

void handle_OnConnect() {

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  timeClient.update(); 
 // server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
 // Temperature += 1;
 // Humidity -= 1;
 // if (Temperature > 35) {
 //   Temperature = 25; Humidity = 85;
 // }
  printf("Temperatura %f\r\n", Temperature);

   String s = MAIN_page;
   s.replace("%TEMP%", String(Temperature));
   s.replace("%HUMI%", String(Humidity));

   s.replace("%HORA%",getDiaHora());
   server.send(200, "text/html", s);
   
   
}

void handle_NotFound(){
  String nofo = Not_Found_Page;
  server.send(404, "text/html", nofo);
}

// processa dia e hora
String getDiaHora(void){
   int dia; // 0 -> domingo, 1 -> segunda, ... 7 -> sabado
   String diaehora;
   dia = timeClient.getDay();
   //Serial.println(String(dia));
   switch(dia){
     case 0: diaehora = "Dom, "; break;
     case 1: diaehora = "Seg, "; break;
     case 2: diaehora = "Ter, "; break;
     case 3: diaehora = "Qua, "; break;
     case 4: diaehora = "Qui, "; break;
     case 5: diaehora = "Sex, "; break;
     case 6: diaehora = "Sab, "; break;
   }
   diaehora += timeClient.getFormattedTime();
   diaehora = diaehora.substring(0,diaehora.length() - 3);
   //Serial.println(diaehora);
   return diaehora;
}
// arduino
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(D0, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  dht.begin();
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  //Server.on(“/page1”,First_page); //”192.168.2.2/page1”  this is first page location
 
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");

  timeClient.begin();
}

void loop() {
  server.handleClient();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
 
  delay(1000);
}


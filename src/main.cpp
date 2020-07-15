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
//https://circuits4you.com/2016/12/16/esp8266-web-server-html/3903000663
//https://randomnerdtutorials.com/esp8266-web-server-spiffs-nodemcu/


#include <Arduino.h>
#include <esp8266wifi.h>
#include <ESP8266WebServer.h>
//#include "ESPAsyncWebServer.h"
#include "index.h"
#include "notfoundpage.h"
#include "temperature.h"
#include "DHT.h"
#include <WiFiUdp.h>
#include "NTPClient.h"
#include <ESP8266mDNS.h>
//#include "time.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// network credentials
const char* ssid = "GVT-34C0";
const char* password = "xxx";

// Set web server port number to 80
ESP8266WebServer  server(80);
//AsyncWebServer  server(80);

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

#define BUFFER_TEMP_SIZE 200
float tempBuf[BUFFER_TEMP_SIZE];
int pnext = 0; 
int qnt_preenchida = 0;
float maxTemp = -200.0;
float minTemp = +500.0;
float medTemp = 0.0;

float maxTempD0, minTempD0, medTempD0 = 0;
float maxTempD1, minTempD1, medTempD1 = 0;
float maxTempD2, minTempD2, medTempD2 = 0;
float maxTempD3, minTempD3, medTempD3 = 0;
float maxTempD4, minTempD4, medTempD4 = 0;
float maxTempD5, minTempD5, medTempD5 = 0;
float maxTempD6, minTempD6, medTempD6 = 0;

//prototypes
String SendHTML(float TempCstat,float Humiditystat);
void handle_OnConnect();
void handle_NotFound();
String getDiaHora(void);

// functions
// Initialize DHT sensor.
DHT dht(dhtpin, DHTTYPE);                
/*
void addBufferTemp(float valor, int buffer_size){
  if (pnext < buffer_size){
    tempBuf[pnext] = valor;
    pnext++;
     if (pnext >= buffer_size) 
       pnext = 0;  

     if (qnt_preenchida < buffer_size){
      qnt_preenchida++;
     }
  }
  else{
    pnext = 0;    
    qnt_preenchida = 0;
  }
}

float calcMedBufferTemp(void){
  float media = 0;
  for (int i =0; i<pnext; i++){
     media += tempBuf[pnext];
  }
  if (qnt_preenchida > 0){
    media = media / qnt_preenchida ;
  }
  return media;
}
*/
void handle_OnConnect() {

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity();       // Gets the values of the humidity 
  timeClient.update(); 

  //addBufferTemp(Temperature, BUFFER_TEMP_SIZE);
  maxTemp = _max(Temperature,maxTemp);
  minTemp = _min(Temperature,minTemp);
  medTemp = _max(minTemp,medTemp);
  medTemp = (maxTemp + minTemp + 7 * medTemp + Temperature)/10;
  int dia = timeClient.getDay(); 

  printf("Temperatura %f\r\n", Temperature);

   String s = MAIN_page;
   s.replace("%TEMP%", String(Temperature));
   s.replace("%HUMI%", String(Humidity));

   s.replace("%HORA%",getDiaHora());
   
   switch (dia){
     case 0:
         maxTempD0 = maxTemp;
         minTempD0 = minTemp;
         medTempD0 = medTemp;
        break;
     case 1:
         maxTempD1 = maxTemp;
         minTempD1 = minTemp;
         medTempD1 = medTemp;
        break;
     case 2:
         maxTempD2 = maxTemp;
         minTempD2 = minTemp;
         medTempD2 = medTemp;
        break;
     case 3:
         maxTempD3 = maxTemp;
         minTempD3 = minTemp;
         medTempD3 = medTemp;
        break;
     case 4:
         maxTempD4 = maxTemp;
         minTempD4 = minTemp;
         medTempD4 = medTemp;
        break;
     case 5:
         maxTempD5 = maxTemp;
         minTempD5 = minTemp;
         medTempD5 = medTemp;
        break;
     case 6:
         maxTempD6 = maxTemp;
         minTempD6 = minTemp;
         medTempD6 = medTemp;
        break;
   }

   s.replace("%MAX_D0%", String(maxTempD0));
   s.replace("%MIN_D0%", String(minTempD0));
   s.replace("%MED_D0%", String(medTempD0));

   s.replace("%MAX_D1%", String(maxTempD1));
   s.replace("%MIN_D1%", String(minTempD1));
   s.replace("%MED_D1%", String(medTempD1));

   s.replace("%MAX_D2%", String(maxTempD2));
   s.replace("%MIN_D2%", String(minTempD2));
   s.replace("%MED_D2%", String(medTempD2));

   s.replace("%MAX_D3%", String(maxTempD3));
   s.replace("%MIN_D3%", String(minTempD3));
   s.replace("%MED_D3%", String(medTempD3));

   s.replace("%MAX_D4%", String(maxTempD4));
   s.replace("%MIN_D4%", String(minTempD4));
   s.replace("%MED_D4%", String(medTempD4));

   s.replace("%MAX_D5%", String(maxTempD5));
   s.replace("%MIN_D5%", String(minTempD5));
   s.replace("%MED_D5%", String(medTempD5));

   s.replace("%MAX_D6%", String(maxTempD6));
   s.replace("%MIN_D6%", String(minTempD6));
   s.replace("%MED_D6%", String(medTempD6));

   server.send(200, "text/html", s);
   
   
}

void handle_NotFound(){
  String nofo = Not_Found_Page;
  server.send(404, "text/html", nofo);
}

/*
void handle_temperatura() {
  String s = Grafico_page;
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  String strTemperatura = String(Temperature);
  //server.send(200, "text/html", s);
  Serial.println("lendo temp");
  server.send_P(200,"text/plain",strTemperatura.c_str());
}
*/

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
  WiFi.hostname("ambiente");
  WiFi.begin(ssid, password);
  MDNS.begin("ambiente");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.hostname());

  server.on("/", handle_OnConnect);
  //Server.on(“/page1”,First_page); //”192.168.2.2/page1”  this is first page location
  //server.on("/temperatura", handle_temperatura);
 
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


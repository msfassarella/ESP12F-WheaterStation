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
//https://electrosome.com/updating-sensor-data-google-spreadsheet-esp8266-iot-project/
//#include <WiFiClientSecure.h> //esp32
//#include <HTTPClient.h>   // Kazushi Mukaiyama
//https://github.com/StorageB/Google-Sheets-Logging
//#include "HTTPSRedirect.h"



#include <Arduino.h>
#include <esp8266wifi.h>
#include <ESP8266WebServer.h>

//#include "ESPAsyncWebServer.h"
#include "index.h"
#include "notfoundpage.h"
#include "configwifipage.h"

#include "temperature.h"
#include "DHT.h"
#include <WiFiUdp.h>
#include "NTPClient.h"
#include <ESP8266mDNS.h>
#include "credentials.h"
//#include <EEPROM.h>
//#include "time.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Set web server port number to 80
ESP8266WebServer  server(80);
//AsyncWebServer  server(80);

// Date & time with NTP
//const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora
const char* servidorNTP = "br.pool.ntp.org";
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
int diaAtual = 0;                           // domingo = 0, segunda = 1, ..., sabado = 6

bool wifiFound = false;

//prototypes
String SendHTML(float TempCstat,float Humiditystat);
void handle_OnConnect();
void handle_NotFound();
String getDiaHora(void);

// functions
// Initialize DHT sensor.
DHT dht(dhtpin, DHTTYPE);                

int restartWhenNewDay(int day, int calculatedDay){
  if (day != calculatedDay) {
    maxTemp = -200.0;
    minTemp = +500.0;
    medTemp = 0.0;
  }
  return (calculatedDay);
}

/**
 * Description: return last valid temperature. 
 *              If sensor has some problem and return is NAN, the valid temperature is the last one. 
 * Input: last temperature
 * Output: a valid temperature
 */
float getTemperature(float lastTemp){
   float temp = dht.readTemperature();   // Gets the values of the temperature
   if (isnan(temp)){
     temp = lastTemp;
   }
   return temp;
}

/**
 * Description: return last valid humidity. 
 *              If sensor has some problem and return is NAN, the valid humidity is the last one. 
 * Input: last humidity
 * Output: a valid humidity
 */
float getHumidity(float lastHumidity){
   float humidity = dht.readHumidity();   // Gets the values of the temperature
   if (isnan(humidity)){
     humidity = lastHumidity;
   }
   return humidity;
}

void handle_OnConnect() {

  Temperature = getTemperature(Temperature); // Gets the values of the temperature
  Humidity = getHumidity(Humidity);          // Gets the values of the humidity 

  maxTemp = _max(Temperature,maxTemp);
  minTemp = _min(Temperature,minTemp);
  medTemp = _max(minTemp,medTemp);
  medTemp = (maxTemp + minTemp + 7 * medTemp + Temperature)/10;
  int diaCalculado = timeClient.getDay(); 
  diaAtual = restartWhenNewDay(diaAtual,diaCalculado);
  Serial.print("dia = ");
  Serial.print(String(diaAtual));Serial.print(" ");
  Serial.println(String(diaCalculado));
  printf("Temperatura %f\r\n", Temperature);

   String s = MAIN_page;
   s.replace("%TEMP%", String(Temperature));
   s.replace("%HUMI%", String(Humidity));

   s.replace("%HORA%",getDiaHora());
   
   switch (diaAtual){
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

void handle_getWifiData() {
  String confwifi = Config_Wifi_Page;          //The page to configure Wifi name
  server.send(404, "text/html", confwifi);
}

void handle_getfunction() {
 String message = "Number of args received:";
 String config_wifi_pw = Config_Wifi_PW_Page;    //The page to configure Wifi password
 String wifiParameter = "wifiName";              //String received from webpage to indicate the type of the data
 String config_wifi_sucess = Config_Wifi_Sucess; //The sucess page
 String config_wifi_erro = Config_Wifi_Erro;     //The erro page

 message += server.args();                       //Get number of parameters
 message += "\n";                                //Add a new line

 for (int i = 0; i < server.args(); i++) {
    message += "Arg nº" + (String)i + " –> ";    //Include the current iteration value
    message += server.argName(i) + ": ";         //Get the name of the parameter
    message += server.arg(i) + "\n";             //Get the value of the parameter
 } 
 Serial.println(message);
 //server.send(200, "text/plain", "Body not received");

 //if (wifiParameter.equals(server.argName(0)) ){      // wifiName
 if (server.argName(0) == "wifiName"){
    server.send(200, "text/html", config_wifi_pw);
    String aux =  String(server.arg(0));
    aux.toCharArray(ssidWifi, aux.length() + 1);
    Serial.print("ssid: "); Serial.println(ssidWifi);
    wifiParameter = "wifiPassword";                   //Reconfigure to next page
 }
 else{
    Serial.print("arg0 = ");
    Serial.println(server.argName(0));
    if (server.argName(0) == "wifiPassword"){
        String aux =  String(server.arg(0));
        aux.toCharArray(passwordWifi, aux.length() + 1);
        Serial.print("pw: "); Serial.println(passwordWifi);
        saveCredentials();
        server.send(200, "text/html",config_wifi_sucess);
    }
    else{
      server.send(200, "text/html",config_wifi_erro);
    }
 }
}

/**
 * brief: Look for a specific wifi ssid
*/
bool lookForWifi(String ssid2Locate){

     const unsigned int SCAN_WAIT_TIME = 5000;
     static unsigned long scanTimePast = 0;
     unsigned long timeNow;
     bool wififound = false;

     timeNow = millis();
    //printf("timepast %lu timenow %lu ",scanTimePast, timeNow);
    if (timeNow - scanTimePast  >= SCAN_WAIT_TIME){
         int n = WiFi.scanNetworks();
         Serial.print("\r\nscan done: ");
         if (n == 0) {
            Serial.println("no networks found");
         } else {
             Serial.print(n);
             Serial.println(" networks found");
             for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
                if (ssid2Locate.equals(WiFi.SSID(i))){
                  Serial.println("rede encontrada");
                  wififound = true;
                  break;
                }
                Serial.print(i + 1);
                Serial.print(": ");
                Serial.print(WiFi.SSID(i));
                Serial.print(" (");
                Serial.print(WiFi.RSSI(i));
                Serial.print(")");
                Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
                  delay(5);
                }
         }
         scanTimePast = timeNow;
    }
    return wififound;
}

// processa dia e hora
String getDiaHora(void){
   int dia; // 0 -> domingo, 1 -> segunda, ... 7 -> sabado
   String diaehora;
   dia = timeClient.getDay();
   Serial.println(String(dia));
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
 
  loadCredentials();
  Serial.print(String(ssidWifi));
  for (unsigned int i =0; i< 5; i++){
     wifiFound = lookForWifi(String(ssidWifi));
     if (wifiFound){
       break;
     }
     Serial.print("loop: "); 
     Serial.println(i);
     delay(5000);
  } 

//wifiFound = false; // teste apenas
  if (wifiFound){
  Serial.print("Connecting to ");
  Serial.print(ssidWifi); Serial.print(" "); Serial.println(passwordWifi); 
  Serial.println(ssidWifi);
  WiFi.hostname("ambiente");
  WiFi.begin(ssidWifi, passwordWifi);
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

  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");

  timeClient.begin();



  }
  else{
    WiFi.softAP("ESP_Inventus", "inventus");
    Serial.print("AP IP address: ");
    IPAddress myIP = WiFi.softAPIP();
    Serial.println(myIP);
    //server.on("/", handle_OnConnect);
    server.on("/", handle_getWifiData);
    server.on("/get", HTTP_GET, handle_getfunction);

    server.begin();
  }
}

void loop() {
  if (wifiFound){
     server.handleClient();
     timeClient.update();
     Temperature = getTemperature(Temperature); // Gets the values of the temperature
     maxTemp = _max(Temperature,maxTemp);
     minTemp = _min(Temperature,minTemp);
     medTemp = _max(minTemp,medTemp);
     medTemp = (maxTemp + minTemp + 7 * medTemp + Temperature)/10;
     int diaCalculado = timeClient.getDay(); 
     diaAtual = restartWhenNewDay(diaAtual,diaCalculado);
     Serial.print("day, time, tnow, tmin, tmed, tmax,");
     Serial.printf(" %d, ",diaAtual);
     Serial.print(timeClient.getFormattedTime());
     printf(", %f, %f, %f, %f\r\n", Temperature, minTemp, medTemp, maxTemp);

  }
  else{
   // Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
   server.handleClient();
  }
  delay(1000);
}


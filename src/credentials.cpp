
#include "Arduino.h"
#include <EEPROM.h>

#define CREDENTIALS_VAR
#include "credentials.h"

/** Load WLAN credentials from EEPROM */
void loadCredentials() {
  EEPROM.begin(512);
  EEPROM.get(0, ssidWifi);
  EEPROM.get(0+sizeof(ssidWifi), passwordWifi);
  char ok[2+1];
  EEPROM.get(0+sizeof(ssidWifi)+sizeof(passwordWifi), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    ssidWifi[0] = 0;
    passwordWifi[0] = 0;
  }
 // Serial.println("Recovered credentials:");
 // Serial.println(ssid);
 // Serial.println(strlen(password)>0?"********":"<no password>");
}


/** Store WLAN credentials to EEPROM */
void saveCredentials(void) {
  EEPROM.begin(512);
  EEPROM.put(0, ssidWifi);
  EEPROM.put(0+sizeof(ssidWifi), passwordWifi);
  char ok[2+1] = "OK";
  EEPROM.put(0+sizeof(ssidWifi)+sizeof(passwordWifi), ok);
  EEPROM.commit();
  EEPROM.end();
}

/**
 *  USE:  for first time use:  
 *        localLoadCredentials();   
 *        saveCredentials();        //save in EEPROM
*/
void localLoadCredentials(void) {
unsigned i;
    char *ssid = "GVT-34C0";
    char* password = "xxxxxxxx";

    for (i = 0; i < 8; i++){
        ssidWifi[i] = *(ssid + i);;
    }
    ssidWifi[i] = '\0';

    for (i = 0; i<10; i++){
        passwordWifi[i] = *(password + i);
    }   
    passwordWifi[i] = '\0'; 
}

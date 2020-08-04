#ifndef CREDENTIALS_h
#define CREDENTIALS_h


#ifdef  CREDENTIALS_VAR
char ssidWifi[32];
char passwordWifi[32];
char serverName[32];
#else
extern char ssidWifi[32];
extern char passwordWifi[32];
extern char serverName[32];
#endif

void loadCredentials(void);
void saveCredentials(void);
void localLoadCredentials(void);

#endif
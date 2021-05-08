#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

struct PushoverMessage
{
public:
	char *message;
	char *title;
	char *url;
	char *url_title;
	bool html;
	uint8_t priority;
	bool sound;
	uint32_t timestamp;
	File * attachment = NULL;
};

class Pushover
{
private:
	uint16_t _timeout = 5000;
	char * _token;
	char * _user;
	FS * fileSystem = &SPIFFS;

public:
	Pushover(char *, char *);
	Pushover();
	int send(PushoverMessage message);
};

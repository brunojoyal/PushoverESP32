#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

struct PushoverMessage
{
public:
	const char *message = "";
	const char *title ="";
	const char *url ="";
	const char *url_title ="";
	bool html = false;
	uint8_t priority =1;
	bool sound = true;
	uint32_t timestamp;
	File * attachment = NULL;
};

class Pushover
{
private:
	uint16_t _timeout = 5000;
	const char * _token;
	const char * _user;
	FS * fileSystem = &SPIFFS;

public:
	Pushover(const char *,const char *);
	Pushover();
	int send(PushoverMessage message);
};

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

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
};

class Pushover
{
private:
	uint16_t _timeout = 5000;
	char * _token;
	char * _user;

public:
	Pushover(char *, char *);
	Pushover();
	int send(PushoverMessage message);
};

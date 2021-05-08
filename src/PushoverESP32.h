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
	const char *title = "";
	const char *url = "";
	const char *url_title = "";
	const char *sound = "";
	bool html = false;
	uint8_t priority = 0;
	uint32_t timestamp;
	File *attachment = NULL;
};

class Pushover
{
private:
	uint16_t _timeout = 5000;
	const char *_token;
	const char *_user;
	FS *_tempfileFS = &SPIFFS;

public:
	Pushover(const char *, const char *);
	Pushover(const char *, const char *, FS *);
	Pushover();
	Pushover(FS * altFS);
	void setUser(const char*);
	void setToken(const char*);
	int send(PushoverMessage message);
};

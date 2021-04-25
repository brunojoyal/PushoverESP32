#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

struct PushoverMessage {
	char * _token;
	char * _user=;
	char * _message=;
	char * _title=;
	char * _url=;
	char * _url_title=;
	bool _html=;
	uint8_t _priority=;
	bool _sound=;
	uint32_t _timestamp;
};

class Pushover
{
private:
	uint16_t _timeout = 5000;
	

public:
	Pushover(char *, char *);
	int send(PushoverMessage message);
};

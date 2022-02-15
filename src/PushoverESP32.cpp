#include <Arduino.h>
#include "PushoverESP32.h"

const char *PUSHOVER_ROOT_CA = "-----BEGIN CERTIFICATE-----\n"
							   "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
							   "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
							   "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
							   "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
							   "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
							   "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
							   "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
							   "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
							   "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
							   "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
							   "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
							   "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
							   "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
							   "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
							   "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
							   "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
							   "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
							   "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
							   "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
							   "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
							   "-----END CERTIFICATE-----\n";

const char *PUSHOVER_API_URL = "https://api.pushover.net/1/messages.json";

Pushover::Pushover(const char *token, const char *user) : _token(token), _user(user), pushoverUploader(Uploader(PUSHOVER_API_URL, PUSHOVER_ROOT_CA, _tempfileFS))
{
	;
}

Pushover::Pushover(const char *token, const char *user, FS *tempfileFS) : _token(token), _user(user), _tempfileFS(tempfileFS), pushoverUploader(Uploader(PUSHOVER_API_URL, PUSHOVER_ROOT_CA, _tempfileFS))
{
	;
}

Pushover::Pushover(FS *tempfileFS) : _tempfileFS(tempfileFS), pushoverUploader(Uploader(PUSHOVER_API_URL, PUSHOVER_ROOT_CA, _tempfileFS))
{
	;
}

Pushover::Pushover() : pushoverUploader(Uploader(PUSHOVER_API_URL, PUSHOVER_ROOT_CA, _tempfileFS))
{
	;
}

int Pushover::send(PushoverMessage newMessage)
{

	
	int responseCode = 0;
	std::map<const char *, const char *> messageData;
		messageData["token"] = _token;
		messageData["user"] = _user;
		messageData["message"] = newMessage.message;
		messageData["title"] = newMessage.title;
		messageData["url"] = newMessage.url;
		messageData["url_title"] = newMessage.url_title;
		messageData["html"] = newMessage.html?"1":"0";
		messageData["priority"] = ((String)newMessage.priority).c_str();
		messageData["sound"] = newMessage.sound;
		messageData["timestamp"] = ((String)newMessage.timestamp).c_str();
	if (!newMessage.attachment)
	{ //No attachment, so just a regular HTTPS POST request.
		HTTPClient myClient;
		myClient.begin(PUSHOVER_API_URL, PUSHOVER_ROOT_CA);
		myClient.addHeader("Content-Type", "application/json");
		StaticJsonDocument<512> doc;
		std::map<const char *, const char *>::iterator it = messageData.begin();
		while(it!=messageData.end()){
			doc[it->first] = it->second;
			it++;
		}
		char output[512];
		serializeJson(doc, output);
		responseCode = myClient.POST(output);

		myClient.end();
	}
	else //attachment, so we enter multipart/form-data hell...
	{
		MultipartMessage message;
		message.file=newMessage.attachment;
		message.otherData = messageData;
		message.contentType="image/jpeg";
		message.name="attachment";
		message.filename="image";
		pushoverUploader.send(message);
	}
	return responseCode;
}

void Pushover::setToken(const char *token)
{
	_token = token;
}

void Pushover::setUser(const char *user)
{
	_user = user;
}

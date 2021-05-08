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

Pushover::Pushover(char *token, char *user) : _token(token), _user(user)
{
	;
}

Pushover::Pushover()
{
	;
}

int Pushover::send(PushoverMessage newMessage)
{

	HTTPClient myClient;
	int responseCode;
	myClient.begin("https://api.pushover.net/1/messages.json", PUSHOVER_ROOT_CA);

	if (!newMessage.attachment)
	{ //No attachment, so just a regular HTTPS POST request.
		myClient.addHeader("Content-Type", "application/json");
		StaticJsonDocument<512> doc;
		doc["token"] = _token;
		doc["user"] = _user;
		doc["message"] = newMessage.message;
		doc["title"] = newMessage.title;
		doc["url"] = newMessage.url;
		doc["url_title"] = newMessage.url_title;
		doc["html"] = newMessage.html;
		doc["priority"] = newMessage.priority;
		doc["sound"] = newMessage.sound;
		doc["timestamp"] = newMessage.timestamp;

		char output[512];
		serializeJson(doc, output);
		responseCode = myClient.POST(output);
	}
	else //attachment, so we enter multipart/form-data hell...
	{
		File * tempFile;
		if(fileSystem->exists("tempfile.temp")){
			fileSystem->remove("tempfile.temp");
		}
		*tempFile = fileSystem->open("tempfile.temp");

		tempFile->print("\n");
		tempFile->print("----abcdefg\n");
		tempFile->print("Content-Disposition: form-data; name=\"user\"\n");
		tempFile->print("\n");
		tempFile->printf("%s\n", _user);
		tempFile->print("----abcdefg\n");
		tempFile->print("Content-Disposition: form-data; name=\"token\"\n");
		tempFile->print("\n");
		tempFile->printf("%s\n", _token);
		tempFile->print("----abcdefg\n");
		tempFile->print("Content-Disposition: form-data; name=\"message\"\n");
		tempFile->print("\n");
		tempFile->printf("%s\n", newMessage.message);
		tempFile->print("----abcdefg\n");
		tempFile->printf("Content-Disposition: form-data; name=\"attachment\"; filename=\"test.jpg\"\n");
		tempFile->print("Content-Type: image/jpeg\n");
		tempFile->print("\n");
		tempFile->close();
		
		while(newMessage.attachment->available()){
			tempFile->write(newMessage.attachment->read());
		}
		tempFile->print("\n");
		tempFile->print("----abcdefg\n");
		myClient.addHeader("Content-Type","multipart/form-data; boundary=--abcdefg\n");
		responseCode = myClient.sendRequest("POST", tempFile, 0);
	}
	myClient.end();
	return responseCode;
}

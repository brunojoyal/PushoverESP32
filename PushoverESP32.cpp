#include "Pushover.h"
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

	// const char *PUSHOVER_ROOT_CA = 				"-----BEGIN CERTIFICATE-----\n"
	// "MIIHLzCCBhegAwIBAgIQBodzVLBzMNnphsWe+m4HSjANBgkqhkiG9w0BAQsFADBe\n"
	// "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
	// "d3cuZGlnaWNlcnQuY29tMR0wGwYDVQQDExRSYXBpZFNTTCBSU0EgQ0EgMjAxODAe\n"
	// "Fw0yMDAyMDMwMDAwMDBaFw0yMjA0MDMxMjAwMDBaMBkxFzAVBgNVBAMMDioucHVz\n"
	// "aG92ZXIubmV0MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAyFo9lgzs\n"
	// "/JVxPxHuG1sbWNQDD6iuwT3LBe65CkL/PE8EGrxdMiDs078ddi/pKwht8xVV1L6D\n"
	// "cP46jG5aEOWdLS6+hbscY0v3E6ey05DTa6YTSaAd+KgzDpunS8xQm03SaHxel3CV\n"
	// "Y2dK6GaBrOZM22Gy1SwhNNySSxnZnxN4JQq9rH50U04UtpyeZkaj1gERJoWcShkf\n"
	// "0VetJPjE0sW9jRYrfUme/lE8WeoLQzjgwruW08FumogmUec48nDfV5GkaTgEqJ8R\n"
	// "vzc9YdPZo2e8xK7+bsQyIdo06bQXz/WQt4JX3h9MW+nj1SDPnrtmpP+g1uUfLX+f\n"
	// "spdTeHn9zNz+yKSJ05csTwRKDg4du0eoOU6KIhHcN6J8m33FAWcXqI/hrK777ugm\n"
	// "jYepqIwUEiJSgglDl219+xOQy+WGvkwUkYJE8zNbIF9xykK1aKRwCxUka2fewcXu\n"
	// "uVt3nkowiBUPovWHbMTzV62XjIS+IHuwCaH/1b8U1Cpki5kDAGOB6KA6FEdVGzR7\n"
	// "8Ky90m1TSdze+MbzFXE6BXtWrvIxjP8+oMvOU6RsrTJn3djyA/bL2LT9sLEPLRnw\n"
	// "sISUOXp5vl95hqESE4Pata4SDUmJT7lPgx3sKF+b5vR0Dae1HG2AsBXOVLhuqTj/\n"
	// "50qKMtXv8HFtgPoU/VvcUAvMPMbwtabvWFcCAwEAAaOCAywwggMoMB8GA1UdIwQY\n"
	// "MBaAFFPKF1n8a8ADIS8aruSqqByCVtp1MB0GA1UdDgQWBBTak5E2/85o6Pbpoaa9\n"
	// "Bt+AiIoPXjAnBgNVHREEIDAegg4qLnB1c2hvdmVyLm5ldIIMcHVzaG92ZXIubmV0\n"
	// "MA4GA1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw\n"
	// "PgYDVR0fBDcwNTAzoDGgL4YtaHR0cDovL2NkcC5yYXBpZHNzbC5jb20vUmFwaWRT\n"
	// "U0xSU0FDQTIwMTguY3JsMEwGA1UdIARFMEMwNwYJYIZIAYb9bAECMCowKAYIKwYB\n"
	// "BQUHAgEWHGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwCAYGZ4EMAQIBMHUG\n"
	// "CCsGAQUFBwEBBGkwZzAmBggrBgEFBQcwAYYaaHR0cDovL3N0YXR1cy5yYXBpZHNz\n"
	// "bC5jb20wPQYIKwYBBQUHMAKGMWh0dHA6Ly9jYWNlcnRzLnJhcGlkc3NsLmNvbS9S\n"
	// "YXBpZFNTTFJTQUNBMjAxOC5jcnQwCQYDVR0TBAIwADCCAXwGCisGAQQB1nkCBAIE\n"
	// "ggFsBIIBaAFmAHUAKXm+8J45OSHwVnOfY6V35b5XfZxgCvj5TV0mXCVdx4QAAAFw\n"
	// "DDeMPAAABAMARjBEAiAt3CBMeotzi7ewPlQoIb5jywJdDJROBZYUcC3A189BzwIg\n"
	// "SfcvUNBASqlVB+II+omWuSQPfG8jhddyvsYOWF14JbkAdgAiRUUHWVUkVpY/oS/x\n"
	// "922G4CMmY63AS39dxoNcbuIPAgAAAXAMN4yHAAAEAwBHMEUCIBgmETHU9/wi5ztW\n"
	// "gk5OiKWUsUk8NmGiE2gcRusKbGxJAiEAnxyxroXKjnG0kv/2d5/2quDBb8rWIYRk\n"
	// "/vwhWimBH30AdQBRo7D1/QF5nFZtuDd4jwykeswbJ8v3nohCmg3+1IsF5QAAAXAM\n"
	// "N4y8AAAEAwBGMEQCIF8BP/B+wKCP8uAZTfuxMS7ip23plKofpSst+QEpJCGqAiBV\n"
	// "vOS5HABKCSdzXw94XaW6PIo1oG770mz0kTKqmknMgTANBgkqhkiG9w0BAQsFAAOC\n"
	// "AQEAmjmGaxnL8EjXLPBtH6pF+YxoE8rVv20txIf5RmoKnkoVKbaJeFJ3475NzUVM\n"
	// "3/NuFn9X452jGlPV/Tz17/e+i2P96eN62cyNU9CFXKV/KK3hWHn6jxRUVupugNGj\n"
	// "b1W7Eu82KZfB/UEaZRkCRtXEAtQs8VAuFrD+C3K5HEYzNYTGInD6W7dq46uc6FFy\n"
	// "j7Y2oTleg3FXafCM9eooYDt2M36wHVd0DOoDWMcPxOpnHjICwDomegEuXMHY5J1M\n"
	// "nRgjCvGPwaP/BTFNdXSIs8AcyAEz3dtF6w86yoDnVXAhMJuxHXSdGJ+zto5YfFTn\n"
	// "ckz9d8LsV2xzD1wkV/4dyIAeHQ==\n"
	// "-----END CERTIFICATE-----\n"
	// "-----BEGIN CERTIFICATE-----\n"
	// "MIIEsTCCA5mgAwIBAgIQCKWiRs1LXIyD1wK0u6tTSTANBgkqhkiG9w0BAQsFADBh\n"
	// "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
	// "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
	// "QTAeFw0xNzExMDYxMjIzMzNaFw0yNzExMDYxMjIzMzNaMF4xCzAJBgNVBAYTAlVT\n"
	// "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
	// "b20xHTAbBgNVBAMTFFJhcGlkU1NMIFJTQSBDQSAyMDE4MIIBIjANBgkqhkiG9w0B\n"
	// "AQEFAAOCAQ8AMIIBCgKCAQEA5S2oihEo9nnpezoziDtx4WWLLCll/e0t1EYemE5n\n"
	// "+MgP5viaHLy+VpHP+ndX5D18INIuuAV8wFq26KF5U0WNIZiQp6mLtIWjUeWDPA28\n"
	// "OeyhTlj9TLk2beytbtFU6ypbpWUltmvY5V8ngspC7nFRNCjpfnDED2kRyJzO8yoK\n"
	// "MFz4J4JE8N7NA1uJwUEFMUvHLs0scLoPZkKcewIRm1RV2AxmFQxJkdf7YN9Pckki\n"
	// "f2Xgm3b48BZn0zf0qXsSeGu84ua9gwzjzI7tbTBjayTpT+/XpWuBVv6fvarI6bik\n"
	// "KB859OSGQuw73XXgeuFwEPHTIRoUtkzu3/EQ+LtwznkkdQIDAQABo4IBZjCCAWIw\n"
	// "HQYDVR0OBBYEFFPKF1n8a8ADIS8aruSqqByCVtp1MB8GA1UdIwQYMBaAFAPeUDVW\n"
	// "0Uy7ZvCj4hsbw5eyPdFVMA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEF\n"
	// "BQcDAQYIKwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADA0BggrBgEFBQcBAQQo\n"
	// "MCYwJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTBCBgNVHR8E\n"
	// "OzA5MDegNaAzhjFodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vRGlnaUNlcnRHbG9i\n"
	// "YWxSb290Q0EuY3JsMGMGA1UdIARcMFowNwYJYIZIAYb9bAECMCowKAYIKwYBBQUH\n"
	// "AgEWHGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwCwYJYIZIAYb9bAEBMAgG\n"
	// "BmeBDAECATAIBgZngQwBAgIwDQYJKoZIhvcNAQELBQADggEBAH4jx/LKNW5ZklFc\n"
	// "YWs8Ejbm0nyzKeZC2KOVYR7P8gevKyslWm4Xo4BSzKr235FsJ4aFt6yAiv1eY0tZ\n"
	// "/ZN18bOGSGStoEc/JE4ocIzr8P5Mg11kRYHbmgYnr1Rxeki5mSeb39DGxTpJD4kG\n"
	// "hs5lXNoo4conUiiJwKaqH7vh2baryd8pMISag83JUqyVGc2tWPpO0329/CWq2kry\n"
	// "qv66OSMjwulUz0dXf4OHQasR7CNfIr+4KScc6ABlQ5RDF86PGeE6kdwSQkFiB/cQ\n"
	// "ysNyq0jEDQTkfa2pjmuWtMCNbBnhFXBYejfubIhaUbEv2FOQB3dCav+FPg5eEveX\n"
	// "TVyMnGo=\n"
	// "-----END CERTIFICATE-----\n"
	// "-----BEGIN CERTIFICATE-----\n"
	// "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
	// "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
	// "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
	// "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
	// "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
	// "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
	// "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
	// "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
	// "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
	// "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
	// "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
	// "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
	// "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
	// "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
	// "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
	// "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
	// "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
	// "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
	// "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
	// "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
	// "-----END CERTIFICATE-----\n";

Pushover::Pushover(String token, String user)
{
	_token = token;
	_user = user;
}
void Pushover::setMessage(String message)
{
	_message = message;
}
void Pushover::setToken(String token)
{
	_token = token;
}
void Pushover::setUser(String user)
{
	_user = user;
}
void Pushover::setDevice(String device)
{
	_device = device;
}
void Pushover::setTitle(String title)
{
	_title = title;
}
void Pushover::setUrl(String url)
{
	_url = url;
}
void Pushover::setUrlTitle(String url_title)
{
	_url_title = url_title;
}
void Pushover::setPriority(int8_t priority)
{
	_priority = priority;
}
void Pushover::setTimestamp(uint32_t timestamp)
{
	_timestamp = timestamp;
}
void Pushover::setSound(String sound)
{
	_sound = sound;
}
void Pushover::setTimeout(uint16_t timeout)
{
	_timeout = timeout;
}
void Pushover::setHTML(boolean html)
{
	_html = html;
}
int Pushover::send(void)
{
	
	HTTPClient myClient;
	
	myClient.begin("https://api.pushover.net/1/messages.json", PUSHOVER_ROOT_CA);
	myClient.addHeader("Content-Type", "application/json"); 
	StaticJsonDocument<512> doc;
	doc["token"]=_token;
	doc["user"]=_user;
	doc["message"]=_message;
	doc["title"]=_title;
	doc["url"]=_url;
	doc["url_title"]=_url_title;
	doc["html"]=_html;
	doc["priority"]=_priority;
	doc["sound"]=_sound;

	doc["timestamp"]=_timestamp;
	char output[512];
	serializeJson(doc, output);
	int code=myClient.POST(output);

	myClient.end();
	return code;

}

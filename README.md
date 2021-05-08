# PushoverESP32

ESP32 library for Pushover.

Originally a fork of [ArduinoHannover/Pushover](https://github.com/ArduinoHannover/Pushover), it has since been completely rewritten, and now support HTTPS and image attachments.

# Usage

Initiate Pushover client:
```cpp
        Pushover pushoverClient(token, user);
```


Messages are encoded within the PushoverMessage struct:

```cpp
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
```

To write a message, simply declare a PushoverMessage object and modify the properties you need. 

```cpp

    PushoverMessage myMessage;

    myMessage.title = "Message title";
    myMessage.message = "Message body";
    pushoverClient.send(myMessage);
```


# Attachments

The library supports sending image attachments as laid out in the Pushover API.

To send an image, simply use the PushoverMessage.attachment property:

```cpp

    PushoverMessage myMessage;

    myMessage.title = "Message title";
    myMessage.message = "Message body";
    File photo = SD.open("/DCIM/123456789.jpg");
    myMessage.attachment = &photo;
    pushoverClient.send(myMessage);
```



**Remark**: Due to the absence of native multipart/form-data support in the arduino-esp32 framework, our current implementation relies on the creation of a tempfile (by default in SPIFFS) which contains the HTTP POST multipart request body. Please do let me know if you have a better way.

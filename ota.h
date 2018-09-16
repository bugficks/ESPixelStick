///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OTA_H__
#define __OTA_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ArduinoOTA.h>
#include "ESPixelStick.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ESPS_ENABLE_ARDUINO_OTA

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern config_t config;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void setupOTA(uint16_t port = 8266)
{
    // Port defaults to 8266
    ArduinoOTA.setPort(port);

    // Hostname defaults to esp8266-[ChipID]
    if (config.hostname)
        ArduinoOTA.setHostname(config.hostname.c_str());

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
        {
            type = "sketch";
        }
        else
        { // U_SPIFFS
            type = "filesystem";
            SPIFFS.end();
        }
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        LOG_PORT.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        LOG_PORT.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        LOG_PORT.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        LOG_PORT.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
        {
            LOG_PORT.println("Auth Failed");
        }
        else if (error == OTA_BEGIN_ERROR)
        {
            LOG_PORT.println("Begin Failed");
        }
        else if (error == OTA_CONNECT_ERROR)
        {
            LOG_PORT.println("Connect Failed");
        }
        else if (error == OTA_RECEIVE_ERROR)
        {
            LOG_PORT.println("Receive Failed");
        }
        else if (error == OTA_END_ERROR)
        {
            LOG_PORT.println("End Failed");
        }
    });
    ArduinoOTA.begin();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // #ifdef ESPS_ENABLE_ARDUINO_OTA

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // #ifndef __OTA_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

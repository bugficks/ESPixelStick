/*
* Mode.h
*
* Project: ESPixelStick - An ESP8266 and E1.31 based pixel driver
* Copyright (c) 2018 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

#ifndef MODE_H_
#define MODE_H_

/* Output Mode - There can be only one! (-Conor MacLeod) */
/*
    not anymore, though you'll most likey get (especially if using FastLED):
        section `.text' will not fit in region `iram1_0_seg'

    try disabling some features here and or in FastLEDDriver.cpp
*/

#define ESPS_MODE_PIXEL
//#define ESPS_MODE_SERIAL
#define ESPS_MODE_FASTLED

#define ESPS_ENABLE_UDPRAW
#define ESPS_ENABLE_ARDUINO_OTA

//#define ESPS_DRIVER_NAME "pixel"
//#define ESPS_DRIVER_NAME "serial"
#define ESPS_DRIVER_NAME "fastled|ws2813"

#endif  // MODE_H_

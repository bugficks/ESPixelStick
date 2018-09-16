///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Driver.h"
#include "PixelDriver.h"
#include "SerialDriver.h"
#include "FastLEDDriver.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(ESPS_MODE_PIXEL) \
    and !defined(ESPS_MODE_SERIAL) \
    and !defined(ESPS_MODE_FASTLED)
// See Mode.h
#error "No valid output mode defined."
#endif

#ifndef ESPS_DRIVER_NAME
// See Mode.h
#error "No valid driver name defined."
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Driver *DriverFactory::create(const String &name)
{
    Driver *driver = 0;

    if(name.indexOf("pixel") == 0)
    {
#if defined(ESPS_MODE_PIXEL)
        driver = new PixelDriver();
#endif
    }
    else if(name == "serial")
    {
#if defined(ESPS_MODE_SERIAL)
        driver = new SerialDriver();
#endif
    }
    else if(name.indexOf("fastled") == 0)
    {
#ifdef ESPS_MODE_FASTLED
        driver = new FastLEDDriver(name);
#endif
    }

    if(!driver)
    {
        LOG_PORT.print("[E] Error creating driver: " );
        LOG_PORT.println(name);
    }

    return driver;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

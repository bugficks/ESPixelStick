///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Driver.h"
#include "PixelDriver.h"
#include "SerialDriver.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #if defined(ESPS_MODE_PIXEL)
// #include "PixelDriver.h"
// PixelDriver     pixels;         // Pixel object
// Driver* driver = &pixels;
// #elif defined(ESPS_MODE_SERIAL)
// SerialDriver    serial;         // Serial object
// Driver* driver = &serial;
// #else
// #error "No valid output mode defined."
// #endif

Driver *DriverFactory::create(const String &name)
{
    Driver *driver = 0;
    if(0){}
#if defined(ESPS_MODE_PIXEL)
    else if(name == "ws2811")
    {
        driver = new PixelDriver();
    }
    else if(name == "fastled")
    {
    }
#endif
#if defined(ESPS_MODE_SERIAL)
    else if(name == "serial")
    {
        driver = new SerialDriver();
    }
#endif
    else
    {

    }

    return driver;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

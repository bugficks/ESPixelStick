///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FastLED DMA version: https://github.com/coryking/FastLED
#define FASTLED_ESP8266_DMA     // GPIO3 RX/D9 pin, ignores DATA_PIN !


//#define FASTLED_FORCE_SOFTWARE_SPI
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#include "FastLEDDriver.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ESPS_MODE_FASTLED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DATA_PIN
#define DATA_PIN        2
#endif

#ifndef CLOCK_PIN
#define CLOCK_PIN       5
#endif

#ifndef COLOR_ORDER
#define COLOR_ORDER     BRG
#endif

#define BRIGHTNESS 50

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int FastLEDDriver::begin(const config_t *config)
{
    // config->pixel_type, config->pixel_color, config->channel_count / 3

    updateOrder(config->pixel_color);

    uint16_t numLeds = config->channel_count / 3;
    if(numLeds != _numLeds)
    {
        if(_leds)
            delete [] _leds;

        _leds = new CRGB[numLeds];
        _numLeds = numLeds;
    }

#if 1
    String nameUpper = _name.c_str();
    nameUpper.toUpperCase();

/*
#define __ADDLEDS_DATA(CS) \
    else if(nameUpper.indexOf(#CS) > 0) \
        { \
            switch(config->pixel_color)\
            { \
                default:\
                case PixelColor::RGB: FastLED.addLeds<CS, DATA_PIN, RGB>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::GRB: FastLED.addLeds<CS, DATA_PIN, GRB>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::BRG: FastLED.addLeds<CS, DATA_PIN, GBR>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::RBG: FastLED.addLeds<CS, DATA_PIN, RBG>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::GBR: FastLED.addLeds<CS, DATA_PIN, BRG>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::BGR: FastLED.addLeds<CS, DATA_PIN, BGR>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
            }\
        }
*/

#define __ADDLEDS_DATA(CS) \
    else if(nameUpper.indexOf(#CS) > 0) \
        { \
            switch(config->pixel_color)\
            { \
                default:\
                case PixelColor::RGB: \
                case PixelColor::GRB: \
                case PixelColor::BRG: \
                case PixelColor::RBG: \
                case PixelColor::GBR: \
                case PixelColor::BGR: \
                FastLED.addLeds<CS, DATA_PIN, COLOR_ORDER>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
            }\
        }

#define __ADDLEDS_SPI(CS) \
    else if(nameUpper.indexOf(#CS) > 0) \
        { \
            switch(config->pixel_color)\
            { \
                default:\
                case PixelColor::RGB: FastLED.addLeds<CS, DATA_PIN, CLOCK_PIN, RGB>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::GRB: FastLED.addLeds<CS, DATA_PIN, CLOCK_PIN, GRB>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::BRG: FastLED.addLeds<CS, DATA_PIN, CLOCK_PIN, GBR>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::RBG: FastLED.addLeds<CS, DATA_PIN, CLOCK_PIN, RBG>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::GBR: FastLED.addLeds<CS, DATA_PIN, CLOCK_PIN, BRG>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
                case PixelColor::BGR: FastLED.addLeds<CS, DATA_PIN, CLOCK_PIN, BGR>(_leds, _numLeds).setCorrection(TypicalLEDStrip); break; \
            }\
        }

    // can't enable all due to :
    // section `.text' will not fit in region `iram1_0_seg'

    if(0){}
    // else if(nameUpper.indexOf("NEOPIXEL") > 0)
    //     FastLED.addLeds<NEOPIXEL, DATA_PIN>(_leds, _numLeds).setCorrection(TypicalLEDStrip);

    // __ADDLEDS_DATA(TM1829)
    // __ADDLEDS_DATA(TM1812)
    // __ADDLEDS_DATA(TM1809)
    // __ADDLEDS_DATA(TM1804)
    // __ADDLEDS_DATA(TM1803)
    // __ADDLEDS_DATA(UCS1903)
    // __ADDLEDS_DATA(UCS1903)
    // __ADDLEDS_DATA(UCS1903B)
    // __ADDLEDS_DATA(UCS1904)
    // __ADDLEDS_DATA(UCS2903)
    __ADDLEDS_DATA(WS2812)
    // __ADDLEDS_DATA(WS2852)
    __ADDLEDS_DATA(WS2812B)
    // __ADDLEDS_DATA(SK6812)
    // __ADDLEDS_DATA(SK6822)
    // __ADDLEDS_DATA(APA106)
    // __ADDLEDS_DATA(PL9823)
    __ADDLEDS_DATA(WS2811)
    __ADDLEDS_DATA(WS2813)
    __ADDLEDS_DATA(APA104)
    __ADDLEDS_DATA(WS2811_400)
    // __ADDLEDS_DATA(GW6205)
    // __ADDLEDS_DATA(GW6205_400)
    // __ADDLEDS_DATA(LPD1886)
    // __ADDLEDS_DATA(LPD1886_8BIT)

#ifdef CLOCK_PINs
    __ADDLEDS_SPI(LPD8806)
    __ADDLEDS_SPI(WS2801)
    __ADDLEDS_SPI(WS2803)
    __ADDLEDS_SPI(SM16716)
    __ADDLEDS_SPI(P9813)
    __ADDLEDS_SPI(APA102)
    __ADDLEDS_SPI(SK9822)
    __ADDLEDS_SPI(DOTSTAR)
#endif

#undef __ADDLEDS_DATA
#undef __ADDLEDS_SPI

#else
    // ESPIChipsets e.g. WS2801, APA102, ...
    //FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(_leds, _numLeds).setCorrection(TypicalLEDStrip);

    // Clockless chipsets
    FastLED.addLeds<WS2813, DATA_PIN, BGR>(_leds, _numLeds).setCorrection(TypicalLEDStrip);
#endif

    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear(true);

    return 0;
}

uint8_t *FastLEDDriver::getData()
{
    return _leds->raw;
}

void FastLEDDriver::show()
{
    FastLED.show();
}

void FastLEDDriver::updateOrder(PixelColor color)
{
    if(_color != color)
    {
        // change FastLED.leds somehow...
        _color = color;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // #ifdef ESPS_MODE_FASTLED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

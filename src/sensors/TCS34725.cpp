#ifdef USE_TCS34725

#include "TCS34725.h"

ColourKit_TCS34725::ColourKit_TCS34725() : sensor() {}

bool ColourKit_TCS34725::begin() {
    return sensor.begin();
}

Colour ColourKit_TCS34725::getColour() {
    sensor.getRawData(&r, &g, &b, &c);
    return Colour(r, g, b);
}

uint16_t ColourKit_TCS34725::getBrightness() {
    sensor.getRawData(&r, &g, &b, &c);
    return c;
}

uint16_t ColourKit_TCS34725::getColourTemp() {
    sensor.getRawData(&r, &g, &b, &c);
    return sensor.calculateColorTemperature_dn40(r, g, b, c);
}

uint16_t ColourKit_TCS34725::getLux() {
    sensor.getRawData(&r, &g, &b, &c);
    return sensor.calculateLux(r, g, b);
}

#endif // USE_TCS34725
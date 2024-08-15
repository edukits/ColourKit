#ifndef COLOUR_KIT_TCS34725_H
#define COLOUR_KIT_TCS34725_H

#include "../ColourKit.h"
#include <Wire.h>
#include <Adafruit_TCS34725.h>

class ColourKit_TCS34725 {
private:
  Adafruit_TCS34725 sensor;
  uint16_t r, g, b, c;

public:
  ColourKit_TCS34725();

  bool begin();
  Colour getColour();
  uint16_t getBrightness();
  uint16_t getColourTemp();
  uint16_t getLux();
};

#endif // COLOUR_KIT_TCS34725_H
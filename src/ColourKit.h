#ifndef COLOUR_KIT_H
#define COLOUR_KIT_H

#include <Arduino.h>

class Colour {
private:
  uint8_t red, green, blue;

public:
  // Constructors
  Colour();
  Colour(int r, int g, int b);
  Colour(uint32_t hexValue);

  // Get individual colour components
  uint8_t getRed() const;
  uint8_t getGreen() const;
  uint8_t getBlue() const;

  // Set individual colour components
  void setRed(uint8_t r);
  void setGreen(uint8_t g);
  void setBlue(uint8_t b);

  // Additive color blending
  Colour& operator+=(const Colour& rhs);

  // Additive color blending
  Colour operator+(const Colour& rhs) const;

  // Subtractive color blending
  Colour& operator-=(const Colour& rhs);

  // Subtractive color blending
  Colour operator-(const Colour& rhs) const;

  // Scale color by a value from 0 to 255 (8-bit scaling)
  Colour& scale(uint8_t scale);

  // Linear interpolation between two colors
  static Colour lerp(const Colour& c1, const Colour& c2, float fraction);

  // Darken by a percentage
  Colour darken(float percent) const;

  // Lighten by a percentage
  Colour lighten(float percent) const;

  // Invert color
  Colour invert() const;

  // Convert to greyscale
  Colour greyscale() const;

  // Format for Adafruit GFX
  operator uint16_t() const;

  // Format for FastLED
  operator uint32_t() const;

  // Write color to LED pins
  void writeLed(byte rPin, byte gPin, byte bPin);
};

#ifdef USE_TCS34725
#include "sensors/TCS34725.h"
#endif

#endif // COLOUR_KIT_H

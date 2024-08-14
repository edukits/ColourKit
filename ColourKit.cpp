#include "ColourKit.h"

Colour::Colour() : red(0), green(0), blue(0) {}

Colour::Colour(int r, int g, int b) : red(r), green(g), blue(b) {}

Colour::Colour(uint32_t hexValue)
  : red((hexValue >> 16) & 0xFF),
    green((hexValue >> 8) & 0xFF),
    blue(hexValue & 0xFF) {}

uint8_t Colour::getRed() const { return red; }
uint8_t Colour::getGreen() const { return green; }
uint8_t Colour::getBlue() const { return blue; }

void Colour::setRed(uint8_t r) { red = r; }
void Colour::setGreen(uint8_t g) { green = g; }
void Colour::setBlue(uint8_t b) { blue = b; }

Colour& Colour::operator+=(const Colour& rhs) {
  red = (red + rhs.red > 255) ? 255 : red + rhs.red;
  green = (green + rhs.green > 255) ? 255 : green + rhs.green;
  blue = (blue + rhs.blue > 255) ? 255 : blue + rhs.blue;
  return *this;
}

Colour& Colour::operator-=(const Colour& rhs) {
  red = (red < rhs.red) ? 0 : red - rhs.red;
  green = (green < rhs.green) ? 0 : green - rhs.green;
  blue = (blue < rhs.blue) ? 0 : blue - rhs.blue;
  return *this;
}

Colour& Colour::scale(uint8_t scale) {
  red = (red * scale) / 255;
  green = (green * scale) / 255;
  blue = (blue * scale) / 255;
  return *this;
}

Colour Colour::lerp(const Colour& c1, const Colour& c2, float fraction) {
  return Colour(
    c1.red + fraction * (c2.red - c1.red),
    c1.green + fraction * (c2.green - c1.green),
    c1.blue + fraction * (c2.blue - c1.blue)
  );
}

Colour Colour::darken(float percent) const {
  float factor = 1.0f - (percent / 100.0f);
  return Colour(
    static_cast<uint8_t>(red * factor),
    static_cast<uint8_t>(green * factor),
    static_cast<uint8_t>(blue * factor)
  );
}

Colour Colour::lighten(float percent) const {
  float factor = 1.0f + (percent / 100.0f);
  return Colour(
    static_cast<uint8_t>(min(255.0f, red * factor)),
    static_cast<uint8_t>(min(255.0f, green * factor)),
    static_cast<uint8_t>(min(255.0f, blue * factor))
  );
}

Colour Colour::invert() const {
  return Colour(255 - red, 255 - green, 255 - blue);
}

Colour Colour::greyscale() const {
  uint8_t gray = static_cast<uint8_t>((red + green + blue) / 3);
  return Colour(gray, gray, gray);
}

Colour::operator uint16_t() const {
  return ((red & 0xF8) << 8) |
         ((green & 0xFC) << 3) |
         (blue >> 3);
}

Colour::operator uint32_t() const {
  return (static_cast<uint32_t>(red) << 16) |
         (static_cast<uint32_t>(green) << 8) |
         static_cast<uint32_t>(blue);
}

void Colour::writeLed(byte rPin, byte gPin, byte bPin) {
  analogWrite(rPin, red);
  analogWrite(gPin, green);
  analogWrite(bPin, blue);
}
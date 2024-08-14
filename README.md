# ColourKit Library

Simple Arduino library for storing, manipulating, and using colour data.

## Install
ColourKit is available in the Arduino Library Manager. The library can be installed using the [standard Arduino library install procedure](http://arduino.cc/en/Guide/Libraries).

## Getting Started

```cpp
#include <ColourKit.h>

Colour(0xffffff);
```

## Basic Use
```cpp
#include <ColourKit.h>

void setup() {
    Colour c1(255, 0, 0); // Red colour
    Colour c2(0, 255, 0); // Green colour

    // Blend colours together
    Colour blended = Colour::lerp(c1, c2, 0.5);

    // Write blended colour to LED on PWM pins (R, G, B) = (9, 10, 11)
    blended.writeLed(9, 10, 11);
}

void loop() {
    // Your loop code here
}
```


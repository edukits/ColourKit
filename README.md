# ColourKit Library

Simple Arduino library for storing, manipulating, and using colour data.

- **Create colours** with RGB or hexadecimal notation
- **Manipulate colours** by blending, scaling, darkening, lightning, inverting, and converting to greyscale
- **Output compatible formats** for [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) and [FastLED](https://github.com/FastLED/FastLED) libraries

## Install
ColourKit is available in the Arduino Library Manager. The library can be installed using the [standard Arduino library install procedure](http://arduino.cc/en/Guide/Libraries).

## Getting Started

Include the `ColourKit.h` header file and create your first Colour:

```cpp
#include <ColourKit.h>

Colour(0xffffff);
```

## Basic Use
Below is a simple sketch that demonstrates blending two colours together and outputting the result to an RGB (common cathode) LED on pins 9, 10, and 11.
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

## Detailed Use

### Creating Colours

There are several ways to create a colour.

#### Using RGB Values

```cpp
Colour myColour(255, 100, 50);  // Red = 255, Green = 100, Blue = 50
```

#### Using a Hexadecimal Value
```cpp
Colour myColour(0xFF6432);  // Equivalent to RGB(255, 100, 50)
```

If you're using a hexadecimal value you found elsewhere, make sure to swap the leading `#` for a `0x`.

#### Default: Dark
```cpp
Colour myColour;  // Defaults to RGB(0, 0, 0)
```

### Setting and Getting Colour Components

#### Setting Colour Components
```cpp
myColour.setRed(200);
myColour.setGreen(150);
myColour.setBlue(100);
```

#### Getting Colour Components
```cpp
uint8_t red = myColour.getRed();
uint8_t green = myColour.getGreen();
uint8_t blue = myColour.getBlue();
```

### Colour Manipulation

#### Additive Blending

Create a new colour by additively blending two existing colours. The blending operation adds the RGB component pairs to create the new RGB value.
```cpp
Colour c1(100, 50, 25);
Colour c2(150, 200, 100);
Colour c3 = c1 + c2;
```

Subtractive blending works similarly to additive blending.
```cpp
Colour c1(200, 150, 100);
Colour c2(50, 50, 50);
Colour c3 = c1 - c2;
```

You can also use the `+=` and `-=` operators to blend a colour value directly.

```cpp
Colour c1(100, 50, 25);
Colour c2(200, 150, 100);
Colour c3(10, 10, 10);

// Brighten c1
c1 += c3;

// Darken c2
c2 -= c2;
```

#### Scaling a Colour

Colours can be scaled by a 1 byte value (from 0-255).

```cpp
Colour myColour(255, 100, 50);
myColour.scale(128);  // Scale down the colour components by 50%
```

#### Interpolating Between Two Colours

Interpolation blends the RGB components of two colours with a specified fraction. This sets the bias of the blending.

```cpp
Colour c1(0, 0, 255);
Colour c2(255, 0, 0);
Colour midColour = Colour::lerp(startColour, endColour, 0.5f);  // 50% blend
```

#### Darkening/Lightening a Colour

The brightness of a colour can be increased by a percentage.

```cpp
Colour darker = myColour.darken(20);    // Darken by 20%
Colour lighter = myColour.lighten(20);  // Lighten by 20%
```

#### Inverting a Colour

```cpp
Colour inverted = myColour.invert();
```

### Converting to Greyscale

```cpp
Colour grey = myColour.greyscale();
```

### Outputting Colours

Any colour can be easily output to specified LED pins using PWM.

```cpp
myColour.writeLed(9, 10, 11);  // Write the color to pins 9 (Red), 10 (Green), 11 (Blue)
```

ColourKit also plays nice with the Adafruit GFX and FastLED libraries.

Colours can be used directly in Adafruit GFX graphics functions.
```cpp
Colour myColour(100, 50, 25);
tft.fillScreen(myColour);
```

Similarly, colours can also be used directly when setting colours with FastLED.

```cpp
Colour myColour(100, 50, 25);
leds[i] = colour;
```
/*

ColourKit Example: Colour Mood Lamp

This example demonstrates the use of the ColourKit library to create a mood lamp
that smoothly transitions between different colors.

Hardware required:
- Arduino board (e.g., Arduino Uno)
- RGB LED (common cathode)
- 3 x 220 ohm resistors

Wiring instructions:
- Connect the common cathode (longest pin) of the RGB LED to GND
- Connect the red pin of the LED to digital pin 9 through a 220 ohm resistor
- Connect the green pin of the LED to digital pin 10 through a 220 ohm resistor
- Connect the blue pin of the LED to digital pin 11 through a 220 ohm resistor

Note: Adjust the TRANSITION_SPEED value to change how quickly the colors change.

*/

#include <ColourKit.h>

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const float TRANSITION_SPEED = 0.01; // Adjust this value to change transition speed

Colour startColor(255, 0, 0);  // Red
Colour endColor(0, 0, 255);    // Blue
float interpolationFactor = 0.0;
bool increasing = true;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Interpolate between start and end colors
  Colour currentColor = Colour::lerp(startColor, endColor, interpolationFactor);
  
  // Write the current color to the LED
  currentColor.writeLed(RED_PIN, GREEN_PIN, BLUE_PIN);
  
  // Update interpolation factor
  if (increasing) {
    interpolationFactor += TRANSITION_SPEED;
    if (interpolationFactor >= 1.0) {
      interpolationFactor = 1.0;
      increasing = false;
    }
  } else {
    interpolationFactor -= TRANSITION_SPEED;
    if (interpolationFactor <= 0.0) {
      interpolationFactor = 0.0;
      increasing = true;
      
      // Swap start and end colors for continuous variation
      Colour temp = startColor;
      startColor = endColor;
      endColor = Colour(random(256), random(256), random(256)); // New random end color
    }
  }
  
  delay(30); // Small delay to control update rate
}
/*

ColourKit Example: Interactive Color Mixer

This example demonstrates advanced uses of the ColourKit library to create an
interactive color mixer using potentiometers and buttons.

Hardware required:
- Arduino board (e.g., Arduino Uno)
- RGB LED (common cathode)
- 3 x 220 ohm resistors
- 3 x potentiometers
- 1 x pushbutton
- 1 x 10k ohm resistor (for button pull-down)

Wiring instructions:
- Connect the common cathode (longest pin) of the RGB LED to GND
- Connect the red pin of the LED to digital pin 9 through a 220 ohm resistor
- Connect the green pin of the LED to digital pin 10 through a 220 ohm resistor
- Connect the blue pin of the LED to digital pin 11 through a 220 ohm resistor
- Connect potentiometers to analog pins A0, A1, and A2
- Connect the pushbutton to digital pin 2 (use 10k pull-down resistor)

Functionality:
- Use potentiometers to adjust R, G, and B values
- Press the button to cycle through color manipulation modes:
  1. Normal (direct color control)
  2. Inverted
  3. Greyscale

*/

#include <ColourKit.h>

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int RED_POT = A0;
const int GREEN_POT = A1;
const int BLUE_POT = A2;

const int BUTTON_PIN = 2;

enum ColorMode {
  NORMAL,
  INVERTED,
  GREYSCALE
};

ColorMode currentMode = NORMAL;
Colour currentColor;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  
  Serial.begin(9600);
  Serial.println("Interactive Color Mixer");
  Serial.println("Use potentiometers to adjust R, G, B values");
  Serial.println("Press the button to cycle through color modes");
}

void loop() {
  // Read potentiometer values and map to 0-255 range
  int redValue = map(analogRead(RED_POT), 0, 1023, 0, 255);
  int greenValue = map(analogRead(GREEN_POT), 0, 1023, 0, 255);
  int blueValue = map(analogRead(BLUE_POT), 0, 1023, 0, 255);
  
  // Create color from potentiometer values
  currentColor = Colour(redValue, greenValue, blueValue);
  
  // Apply color manipulation based on current mode
  switch (currentMode) {
    case NORMAL:
      // No manipulation needed
      break;
    case INVERTED:
      currentColor = currentColor.invert();
      break;
    case GREYSCALE:
      currentColor = currentColor.greyscale();
      break;
  }
  
  // Write the current color to the LED
  currentColor.writeLed(RED_PIN, GREEN_PIN, BLUE_PIN);
  
  // Check for button press to change mode
  if (digitalRead(BUTTON_PIN) == HIGH) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      currentMode = static_cast<ColorMode>((currentMode + 1) % 3);
      Serial.print("Mode changed to: ");
      Serial.println(getModeString(currentMode));
      lastDebounceTime = millis();
    }
  }
  
  // Print color values to serial monitor
  Serial.print("R: ");
  Serial.print(currentColor.getRed());
  Serial.print(" G: ");
  Serial.print(currentColor.getGreen());
  Serial.print(" B: ");
  Serial.print(currentColor.getBlue());
  Serial.print(" Mode: ");
  Serial.println(getModeString(currentMode));
  
  delay(100); // Small delay to limit serial output rate
}

String getModeString(ColorMode mode) {
  switch (mode) {
    case NORMAL:
      return "Normal";
    case INVERTED:
      return "Inverted";
    case GREYSCALE:
      return "Greyscale";
    default:
      return "Unknown";
  }
}
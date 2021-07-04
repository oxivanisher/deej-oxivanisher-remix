#include <Arduino.h>
#include <FastLED.h>

//fastLED

const int LED_PIN = 5;
const int NUM_LEDS = 6;
const int brightness = 30;
CRGB leds[NUM_LEDS];
//                                   {{LED1} Gaming, {LED2} Vivaldi, {LED3} Spotify, {LED4} Discord, {LED5}} Windows System,{LED6}} Rest;
const int high_colors[NUM_LEDS][3] = {{155, 48, 255}, {228, 61, 64}, {30, 215, 96}, {114, 137, 218}, {0, 161, 241}, {114, 137, 21}};
const int low_colors[NUM_LEDS][3] = {{20, 5, 25}, {23, 6, 6}, {3, 21, 10}, {11, 14, 22}, {0, 16, 24}, {11, 14, 2}};

//Deej
const int NUM_SLIDERS = 6;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A6, A7};

int analogSliderValues[NUM_SLIDERS];

void setup() {
  //FastLed Init
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(low_colors[i][0], low_colors[i][1], low_colors[i][2]);
  }

  FastLED.show();
  // Deej Pot Inputs
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(9600);
}

int colortransition(int index, int color, int multip) {  //Function to do the actual transition for the color channels using the differential between the high and low values with 20 steps
  int value = 0;
  int steps = 0;
  if (low_colors[index][color] <= high_colors[index][color]) {
    steps = (high_colors[index][color] - low_colors[index][color]) / 20;
    if ((low_colors[index][color] + (steps * multip)) <= high_colors[index][color]) {
      value = low_colors[index][color] + (steps * multip);
      //Serial.println(String("R Done ") + r);
    } else {
      value = high_colors[index][color];
    }
  } else {
    steps = (low_colors[index][color] - high_colors[index][color]) / 20;
    if ((low_colors[index][color] - (steps * multip)) <= high_colors[index][color]) {
      value = high_colors[index][color];
    } else {
      value = low_colors[index][color] - (steps * multip);
    }
  }

  return value;
}

void colorchange(int index, float input) {
  int r = 0;
  int g = 0;
  int b = 0;
  float multipf = (input / 1024) * 20;
  int multip = multipf;
  r = colortransition(index, 0, multip);
  g = colortransition(index, 1, multip);
  b = colortransition(index, 2, multip);

  leds[index] = CRGB(r, g, b);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    analogSliderValues[i] = analogRead(analogInputs[i]);
    // reuse the analog read value to change the color of the LED associated to that input
    colorchange(i, analogSliderValues[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void loop() {
  updateSliderValues();
  sendSliderValues();  // Actually send data (all the time)
  // printSliderValues();  // For debug
  FastLED.show();
  delay(10);
}

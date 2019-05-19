# LED-SpectrumAnalyzer
Arduino-Based Music Spectrum Analyzer. Code still in development

## A brief Introduction
A spectrum analyzer takes as input music, specifically its sine wave, and processes it giving as output the amplitude of the various frequencies.

## Code
[Still in Development] This program can be run on a single Arduino through LEDMatrix.ino. For a more optimized and elegant result, you can also run it on two Arduino, a Slave one that processes data and a Master one that recieves the processed array through `Serial` and draws the graphics onto the Matrix.

## Hardware
- Arduino Nano
- WS2812B RGB LEDS (x300) laid down as a serpentine-like vector, seen as a matrix.

Data from music is fetched connecting one of the leads of the 3.5mm jack to an analogPin set to `INPUT`. This way the Arduino keeps reading the different voltage levels, which are the values of the sine wave. 

## External Libraries
### <FastLED.h>
Easy to use library to work with neopixel-like leds in a fast and efficient way.

### <fix_fft.h>
This library is used to perform a Fast Fourier Transform. It is given as input an array containing the values read from `analogRead()`.

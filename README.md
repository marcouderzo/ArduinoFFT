# LED-SpectrumAnalyzer
Arduino-Based Music Spectrum Analyzer.

## A brief Introduction
A spectrum analyzer takes as input music, specifically its sine wave, and processes it giving as output the amplitude of the various frequencies.

## Hardware
- Arduino Nano
- WS2812B RGB LEDS (x300) laid down as a serpentine-like vector, seen as a matrix.

Data from music is fetched connecting one of the leads of the 3.5mm jack to an analogPin set to `INPUT`.

## External Libraries
### <FastLED.h>
Easy to use library to work with neopixel-like leds in a fast and efficient way.

### <fix_fft.h>
This library is used to perform a Fast Fourier Transform. It is given as input an array containing the values read from `analogRead()`.

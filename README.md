# LED-SpectrumAnalyzer
Arduino-Based Music Spectrum Analyzer.

## A brief Introduction
A spectrum analyzer takes as input music, specifically its sine wave, and processes it giving as output the amplitude of the various frequencies.

## Hardware
- Arduino Nano
- WS2812B RGB LEDS (x300) laid down as a serpentine-like vector, seen as a matrix.

Data from music is fetched connecting one of the leads of the 3.5mm jack to an analogPin set to `INPUT`. This way the Arduino keeps reading the different voltage levels, which are the values of the sine wave. Then an FFT is performed and the output is pushed to the matrix.

## External Libraries
### <FastLED.h>  - from https://github.com/FastLED/FastLED
Easy to use library to work with neopixel leds (and similar chipsets, in my case WS2812B).

### <LedMatrix.h>  - from https://github.com/Jorgen-VikingGod/LEDMatrix
This library works in conjunction with `FastLED.h`. It builds the array used by `FastLED.h` and draws the graphics.

### <fix_fft.h>  - from https://github.com/kosme/fix_fft
This library is used to perform a Fast Fourier Transform. It is given as input an array containing the values read from `analogRead()`.
The output of the FFT is a sequence of complex numbers. Each complex number is a pair consisting of a real part and an imaginary part. To graph the power spectral density of the audio, you only need to use the first N/2 values of the FFT output array.

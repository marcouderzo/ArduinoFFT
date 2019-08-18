![git/readme_img.png]

# MusicSpectrumVisualizer
A Neopixel Arduino-Based Music Spectrum Analyzer.

## A brief Introduction
A spectrum analyzer takes as input music, specifically its sine wave, and processes it giving as output the amplitude of the various frequencies.

## Hardware
- Arduino Nano
- WS2812B RGB LEDS (x300) laid down as a serpentine vector (zig-zag), forming a virtual matrix.

Data from music is fetched connecting one of the leads of the 3.5mm jack to an analogPin set to `INPUT`. This way the Arduino keeps reading the different voltage levels, which are the values of the sine wave. Then an FFT is performed and the output is pushed to the matrix.

## External Libraries
### <FastLED.h>
Easy to use library to work with neopixel leds (and similar chipsets, in my case WS2812B).

### <LedMatrix.h> 
This library works in conjunction with `FastLED.h`. It builds the array used by `FastLED.h` and draws the graphics.

### <fix_fft.h> 
This library is used to perform a Fast Fourier Transform, which transposes the sine wave from the time domain to the frequency domain. It is given as input an array containing the values read from `analogRead()`.
The output of the FFT is a sequence of complex numbers. To graph the power spectral density of the audio, which is what most people want from the FFT, you only need to use the first N/2 values of the output array.

## GUI Control
The Arduino can be controlled through a GUI, created in QT. The GUI establishes a connection with the Arduino using the Serial Port, `<QSerialPort>`, and sends serial signals to control the matrix.

### Functions
- Switch Color Palettes
- Switch between Full Spectrum and Bass Spectrum

-> Adjust Amplitude Sensitivity

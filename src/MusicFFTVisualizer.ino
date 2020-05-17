#include <FastLED.h>
#include <LEDMatrix.h>
#include <fix_fft.h>   //to get input from audio source, connect audio output to Analog 0.

#define mHeight 15
#define mWidth 20
#define mSize (mWidth*mHeight)
#define mLayout VERTICAL_ZIGZAG_MATRIX
#define DATA_PIN 12
#define audioPin A5 // Left or right channel audio positive lead connects here
#define buttonPin 10 
#define maxFreqAmplitude 40   // Change this value to adjust the sensitivity

char data[128], im[128];  // FFT Array Variables
char data_out[20];

int color_command = 0;

//********************************************** Defining Custom RGB Palettes

// Position, Gval, Rval, Bval

DEFINE_GRADIENT_PALETTE(BlueToRed)
{
  0, 0, 0, 255,
  255,  255, 0, 0
};

//**********************************************

cLEDMatrix < mWidth, mHeight, mLayout > leds;

CRGBPalette16 hue;

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
  FastLED.setBrightness(70);
  //Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 128; i++)
  {
    data[i] = analogRead(audioPin);
    im[i] = 0;
  }

  fix_fft(data, im, 7, 0);

  for (int i = 0; i < 64; i++) // only need N/2 elements of the array
  {
    data[i] = sqrt(data[i] * data[i] + im[i] * im[i]);
  }

  for (int i = 0; i < 20; i++)
    data_out[i] = (data[i * 3] + data[i * 3 + 1] + data[i * 3 + 2])/3;
 

  for (int i = 0; i < 20; i++)
    data_out[i] = map(data_out[i], 0, maxFreqAmplitude, 0, mHeight);
  
  FastLED.clear();

  for (int i = 0; i < mWidth; i++)
  {
    leds.DrawLine(i, 0, i, data_out[i], ColorFromPalette(BlueToRed, 12 * i));
  }
  
  FastLED.show();
}

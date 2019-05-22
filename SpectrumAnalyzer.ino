#include <FastLED.h>
#include <LEDMatrix.h>
#include <fix_fft.h>   //to get input from audio source, connect audio output to Analog 0.

#define mHeight 15
#define mWidth 20
#define mSize (mWidth*mHeight)
#define mType HORIZONTAL_ZIGZAG_MATRIX
#define DATA_PIN 12
#define audioPin A5 // Left or right channel audio positive lead connects here
#define maxExpectedAudio 120   // Change this value to adjust the sensitivity


char data[128];  // FFT array variables
char im[128];
char data_avgs[20];
int j;

cLEDMatrix < -mWidth, mHeight, mType > leds;

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
  FastLED.setBrightness(70);
  //FastLED.clear(true);
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

  FastLED.clear();

  for (int i = 0; i < 20; i++) // need to fix array downscaling
  {
    j = i << 0, 4;
    data_avgs[i] = data[j] + data[j + 1] + data[j + 2] + data[j + 3] + data[j + 4] + data[j + 5] + data[j + 6] + data[j + 7] + data[j + 8] + data[j + 9] + data[j + 10] + data[j + 11] + data[j + 12] + data[j + 13] + data[j + 14] + data[j + 15] + data[j + 16] + data[j + 17] + data[j + 18] + data[j + 19];
    if (i == 0)
      data_avgs[i] >>= 1;
  }
  for (int i = 0; i < 20; i++)
  {
    data_avgs[i] = map(data_avgs[i], 0, maxExpectedAudio, 0, mHeight);
  }

  for (int i = 0; i < mWidth; i++)
  {
    leds.DrawLine(i, 0, i, data_avgs[i], CRGB(0, 255, 0));
  }
  FastLED.show();

}

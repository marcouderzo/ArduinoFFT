#include <FastLED.h>
#include <LEDMatrix.h>
#include <fix_fft.h>   //to get input from audio source, connect audio output to Analog 0.

#define mHeight 15
#define mWidth 20
#define mSize (mWidth*mHeight)
#define mType HORIZONTAL_ZIGZAG_MATRIX
#define DATA_PIN 12
#define audioPin A5 // Left or right channel audio positive lead connects here
#define maxFreqAmplitude 40   // Change this value to adjust the sensitivity

char data[128], im[128];  // FFT Array Variables
char data_avgs[20];

cLEDMatrix < -mWidth, mHeight, mType > leds;

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
  FastLED.setBrightness(70);
  //FastLED.clear(true);
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

  for (int i = 0; i < 20; i++) //average values into a smaller array to fit the matrix width
  {
    data_avgs[i] = data[i * 3] + data[i * 3 + 1] + data[i * 3 + 2];
    if (i == 0) data_avgs[i] >>= 1;  // de-emphasize first band, as it is too sensitive
  }


  for (int i = 0; i < 20; i++)
  {

    data_avgs[i] = map(data_avgs[i], 0, maxFreqAmplitude, 0, mHeight);

  }

  for (int i = 0; i < mWidth; i++)
  {
    leds.DrawLine(i, 0, i, data_avgs[i], CRGB(255 - 12 * i, 0, 12 * i)); //use a switch() to change set of colours
  }
  FastLED.show();

}

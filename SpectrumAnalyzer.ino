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

int mode = 0;
int serial_read=1;

cLEDMatrix < mWidth, mHeight, mLayout > leds;




//********************************************** Defining Custom RGB Palettes

// Position, Gval, Rval, Bval

DEFINE_GRADIENT_PALETTE(BlueToRed)
{
  0, 0, 0, 255,
  255,  255, 0, 0
};

DEFINE_GRADIENT_PALETTE(PinkToRed)
{
  0, 255, 0, 255,
  255, 255, 0, 0
};

DEFINE_GRADIENT_PALETTE(skyline)
{
  0, 20, 136, 204,
  128, 47, 43, 178,
  255, 0, 0, 255
};


DEFINE_GRADIENT_PALETTE(GreenBlue) {
  0, 17, 80, 255,
  255, 0, 255, 0
};

//**********************************************

CRGBPalette16 hue;

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
  FastLED.setBrightness(70);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
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


  for (int i = 0; i < 20; i++) //average values into a smaller array to fit the matrix width
  {
    data_out[i] = data[i * 3] + data[i * 3 + 1] + data[i * 3 + 2];
    if (i == 0) data_out[i] >>= 1;
  }


  for (int i = 0; i < 20; i++)
  {
    data_out[i] = map(data_out[i], 0, maxFreqAmplitude, 0, mHeight);
  }

//*************************** Serial Comunication

  if(Serial.available() > 0)
  {
    serial_read = Serial.read();
    Serial.print(serial_read);
  }

  if(serial_read)
  {
    switch (serial_read) 
    {
      case 49:
        hue = BlueToRed;
        break;
      case 50:
        hue = PinkToRed;
        break;
      case 51:
        hue = skyline;
        break;
      case 52:
        hue = GreenBlue;
        break;
      case 53:
        hue = Rainbow_gp;
        break;
      case 54:
        hue = CloudColors_p;
        break;
      case 55:
        hue = LavaColors_p;
        break;
      case 56:
        hue = OceanColors_p;
        break;
      default:
        hue = skyline;
    }
  }  

//******************************

  FastLED.clear();

  for (int i = 0; i < mWidth; i++)
  {
    leds.DrawLine(i, 0, i, data_out[i], ColorFromPalette(hue, 12 * i));
  }
  FastLED.show();
}

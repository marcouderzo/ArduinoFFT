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

int serial_input;
int range_command;
int color_command;

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

DEFINE_GRADIENT_PALETTE(Pizelex) {
  0, 17, 67, 87,
  255, 242, 148, 146
};

DEFINE_GRADIENT_PALETTE(Netflix) {
  0, 142, 14, 0,
  255, 133, 129, 125
};

DEFINE_GRADIENT_PALETTE(Summer) {
  0, 168, 255, 120,
  255, 120, 255, 214
};

DEFINE_GRADIENT_PALETTE(Wedding) {
  0, 64, 224, 208,
  128, 255, 140, 0,
  255, 255, 0, 128
};

DEFINE_GRADIENT_PALETTE(IbizaSunset) {
  0, 238, 9, 121,
  255, 255, 106, 0
};

DEFINE_GRADIENT_PALETTE(Aquamarine) {
  0, 26, 41, 128,
  255, 38, 208, 206
};




//**********************************************

cLEDMatrix < mWidth, mHeight, mLayout > leds;

void parse_serial_input()
{
  if (serial_input == 48 || serial_input == 49)
  {
    range_command = serial_input;
    return;
  }
  else
  {
    color_command = serial_input;
    return;
  }
  return;
}

CRGBPalette16 hue;

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
  FastLED.setBrightness(70);
  pinMode(buttonPin, INPUT);  //deprecated: using GUI
  Serial.begin(9600);
}

void loop()
{

  if (Serial.available() > 0)
  {
    serial_input = Serial.read();
    parse_serial_input();
  }


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

  if (range_command == 49)  //Bass Frequency Range
  {
    data_out[1] >>= 3;
    data_out[2] >>= 1;
  }
  else  //Complete Frequency Range
  {
    for (int i = 0; i < 20; i++)
    {
      data_out[i] = data[i * 3] + data[i * 3 + 1] + data[i * 3 + 2];
      if (i == 0) data_out[i] >>= 1;
    }
  }

  for (int i = 0; i < 20; i++)
  {
    data_out[i] = map(data_out[i], 0, maxFreqAmplitude, 0, mHeight);
  }


  switch (color_command)  // serial commands are sent as ASCII code, so Arduino will read them as integers ranging from 97-106
  {
    case 97:
      hue = BlueToRed;
      break;
    case 98:
      hue = PinkToRed;
      break;
    case 99:
      hue = skyline;
      break;
    case 100:
      hue = GreenBlue;
      break;
    case 101:
      hue = Rainbow_gp;
      break;
    case 102:
      hue = Pizelex;
      break;
    case 103:
      hue = Netflix;
      break;
    case 104:
      hue = Summer;
      break;
    case 105:
      hue = Wedding;
      break;
    case 106:
      hue = IbizaSunset;
      break;
    case 107:
      hue = Aquamarine;
      break;
    default:
      hue = BlueToRed;
  }
  
  FastLED.clear();

  int k = 1;
  if (range_command == 49)
  {
    for (int i = 0; i < mWidth; i += 2)
    {
      leds.DrawLine(i, 0, i, data[k], ColorFromPalette(hue, 12 * i));
      leds.DrawLine(i + 1, 0, i + 1, data[k], ColorFromPalette(hue, 12 * i));
      k++;
    }
  }
  else
  {
    for (int i = 0; i < mWidth; i++)
    {
      leds.DrawLine(i, 0, i, data_out[i], ColorFromPalette(hue, 12 * i));
    }
  }
  FastLED.show();
}

#include <FastLED.h>
#include <fix_fft.h>   //to get input from audio source, connect audio output to Analog 0.

#define NUM_LEDS 300
#define DATA_PIN 12
#define mHeight 15
#define mWidth 20
const int audioPin = A0; // Left or right channel audio positive lead connects here
#define maxExpectedAudio 120   // Change this value to adjust the sensitivity


CRGB leds[NUM_LEDS];
char data[20];  // FFT array variables
char im[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint16_t pixel;

uint16_t XYTable[]={
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
    39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,
    40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
    79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,  64,  63,  62,  61,  60,
    80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,
   119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,
   120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
   159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140,
   160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
   199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180,
   200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
   239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220,
   240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259,
   279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260,
   280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299
  };



//**************************
/*
    @documentation: getPixel() takes x y values, calculates the LED position considering the matrix 
    is a serpentine-like vector, and returns index used to identify LED in leds[] array. uint8_t is an unsigned 
    8bit char type, used instead of int to save heap memory. This way SRAM is unlikely to get filled.

    @optimization: possibly cleaner: if(y%2==0) y*mWidth+reverseX. if row(y)is even, with row(i)being i*mWidth. This way the 
    XYTable[] array wouldn't be necessary as "i" could be used directly as the index of CRGB leds[] array.
*/

uint16_t getPixel(int x, int y) 
{
  uint16_t i = (y * mWidth) + x;
  uint16_t j = XYTable[i];
  return j;
}

//**************************
/*
    @documentation: pushBar() draws the frequency columns and their current intensity according to the values processed by fix_fft()
*/

void pushBar (int x, int y)
{
  for (int i = 0; i<y; i++)
  {
    pixel=getPixel(x,i);
    leds[pixel] = CRGB(255, 0, 0);
  }
    FastLED.show();
}

void setup() 
{
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(70);
  //Serial.begin(9600); //debugging and testing

}


void loop() 
{ 
  for (int i = 0; i < 40; i++) 
  {
    data[i] = analogRead(A5);
    map(data[i],0,1023,0,maxExpectedAudio);
  }

  fix_fft(data, im, mWidth, 0);  

  //ledarray(20,300)=CRGB(0,0,0); // use this instead on clear() if you want the first row not to visibly cycle 
  
  FastLED.clear();
  
  for(int i=mWidth-1; i>=0; i--)
  {
    // data[i] = sqrt(data[i]*data[i] + im[i]*im[i]);
    data[i] = map(data[i],0,maxExpectedAudio,1,mHeight);
    pushBar(i, data[i]);
  }
  delayMicroseconds(500); 
}

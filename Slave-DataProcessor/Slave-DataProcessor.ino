#include <fix_fft.h>
#define maxExpectedAudio 120

char data[20];  // FFT array variables 
char im[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};

char outData[20];

const int wait =3;

void setup() {
  Serial.begin(9600); //check baud update frequency
  pinMode(wait,INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  for (int i = 0; i < 20; i++) 
  {
    data[i] = analogRead(A3);
    map(data[i],0,1023,0,maxExpectedAudio);
    //int d=data[i];
   // Serial.println(d);
    
  }

  fix_fft(data, im, 20, 0);

  for(int i=0; i<20;i++)
  {
    data[i] = map(data[i],0,maxExpectedAudio,1,15);
  }

 for(int i=0; i<20; i++)
 {
  int d=data[i];
  Serial.write(d);
 }
  
}

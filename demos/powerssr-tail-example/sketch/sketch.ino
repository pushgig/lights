/*
 Dim_PSSR_ZC_Tail
 
 This sketch is a sample sketch using the ZeroCross Tail(ZCT)to generate a sync
 pulse to drive a PowerSSR Tail(PSSRT) for dimming ac lights.
 
 Connections to an Arduino Duemilanove:
 1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm pull up to Arduino 5V.
 2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
 3. Connect the PowerSSR Tail +in terminal to digital pin 4 and the -in terminal to Gnd.
 
 
*/

#include <Ramp.h> // Add RAMP library
#include <TimerOne.h>                    

volatile int cnt1 = 0;               // Variable to use as a counter
volatile int cnt2 = 0;

volatile boolean zero_cross1 = 1;  // Boolean to store a "switch" to tell us if we have crossed zero
volatile boolean zero_cross2 = 1;
int PSSR1 = 4;                  // PowerSSR Tail connected to digital pin 4
int PSSR2 = 5;                  // PowerSSR Tail connected to digital pin 5
int dim1 = 100;                   // Default dimming level (0-128)  0 = on, 128 = off
int dim2 = 100;
int freqStep = 60;              // Set to 60hz mains
int LED = 0;                    // LED on Arduino board on digital pin 13
ramp dimRamp1;
ramp dimRamp2;

void setup()
{
  Serial.begin(9600);
  
 pinMode(LED, OUTPUT);
 pinMode(PSSR1, OUTPUT);                // Set SSR1 pin as output
 pinMode(PSSR2, OUTPUT);                // Set SSR2 pin as output
 attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to digital pin 2 (interupt 0),
 Timer1.initialize(freqStep);
 Timer1.attachInterrupt(dim_check, freqStep);
 
 dimRamp1.go(128);
 dimRamp2.go(128);
 
 dimRamp1.go(80, 125, LINEAR, FORTHANDBACK);
 dimRamp2.go(80, 1000, LINEAR, FORTHANDBACK);   
}


void loop()                        // Main loop
{
// dim = 120;
// delay(500);
// dim = 100;
// delay(500);
// dim = 80;
// delay(500);
// dim = 60;
// delay(500);
// dim = 40;
// delay(500);
// dim = 20;
// delay(500);
// dim = 0;
// delay(500);
dim1 = dimRamp1.update();
dim2 = dimRamp2.update();
}

// Functions
void dim_check() {
  boolean burn1 = 0;
  boolean burn2 = 0;
  
  if(zero_cross1 == 1) {
    if(cnt1 >= dim1) {
      burn1 = 1;
      zero_cross1 = 0;
      cnt1 = 0;
    } else {
      cnt1++;
    }
  }
  
  if(zero_cross2 == 1) {
    if(cnt2 >= dim2) {
      burn2 = 1;
      zero_cross2 = 0;
      cnt2 = 0;
    } else {
      cnt2++;
    }
  }
    
  if (burn1 == 1 || burn2 == 1) {
    delayMicroseconds(100);
    
    if (burn1 == 1) {
      digitalWrite(PSSR1, HIGH);
    }
    
    if (burn2 == 1) {
      digitalWrite(PSSR2, HIGH);
    }
    
    delayMicroseconds(50);
    
    if (burn1 == 1) {
      digitalWrite(PSSR1, LOW);
    }
    
    if (burn2 == 1) {
      digitalWrite(PSSR2, LOW);
    }
  }
}

void zero_cross_detect() 
{
  // Serial.println("zero cross detect"); 
   zero_cross1 = 1;
   zero_cross2 = 1;
   // set the boolean to true to tell our dimming function that a zero cross has occured
} 

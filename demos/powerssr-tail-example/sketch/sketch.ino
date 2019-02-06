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

volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int PSSR1 = 4;                  // PowerSSR Tail connected to digital pin 4
int dim = 100;                   // Default dimming level (0-128)  0 = on, 128 = off
int freqStep = 60;              // Set to 60hz mains
int LED = 0;                    // LED on Arduino board on digital pin 13
ramp dimRamp;

void setup()
{
  Serial.begin(9600);
  
 pinMode(LED, OUTPUT);
 pinMode(PSSR1, OUTPUT);                // Set SSR1 pin as output
 attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to digital pin 2 (interupt 0),
 Timer1.initialize(freqStep);
 Timer1.attachInterrupt(dim_check,freqStep);
 
 dimRamp.go(128);
 dimRamp.go(80, 10000, LINEAR, FORTHANDBACK);   
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
dim = dimRamp.update();
}

// Functions

void dim_check() {                  // This function will fire the triac at the proper time
 // Serial.println("dim_check: "); 
 // Serial.print(zero_cross);
 
 if(zero_cross == 1) {              // First check to make sure the zero-cross has happened else do nothing
   if(i>=dim) {
     // Serial.println("fire PSSR");
    delayMicroseconds(100);        //These values will fire the PSSR Tail.
    digitalWrite(PSSR1, HIGH);
    delayMicroseconds(50);
    digitalWrite(PSSR1, LOW); 
     i = 0;                         // Reset the accumulator
     zero_cross = 0;                // Reset the zero_cross so it may be turned on again at the next zero_cross_detect    
   } else {
     i++;                           // If the dimming value has not been reached, increment the counter
   }                                // End dim check
 }                                  // End zero_cross check
}

void zero_cross_detect() 
{
  // Serial.println("zero cross detect"); 
   zero_cross = 1;
   // set the boolean to true to tell our dimming function that a zero cross has occured
} 

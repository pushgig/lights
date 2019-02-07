/*
 Dim_PSSR_ZC_Tail

 This sketch is a sample sketch using the ZeroCross Tail(ZCT)to generate a sync
 pulse to drive a PowerSSR Tail(PSSRT) for dimming ac lights.

 Connections to an Arduino Duemilanove:
 1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm pull up to Arduino 5V.
 2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
 3. Connect the PowerSSR Tail +in terminal to digital pin 4 and the -in terminal to Gnd.


*/

#include <TimerOne.h>
#include "PowerSSR.h"

int PSSR1 = 4;                  // PowerSSR Tail connected to digital pin 4
int PSSR2 = 5;                  // PowerSSR Tail connected to digital pin 5
int LED = 0;                    // LED on Arduino board on digital pin 13
const int NUM_SSRS = 2;

// Set to 60hz mains for now
int freqStep = 60;

PowerSSR ssrs[NUM_SSRS];

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].init(i + 4);
  }

  ssrs[0].go(100, 125, LINEAR, FORTHANDBACK);
  ssrs[1].go(100, 1000, LINEAR, FORTHANDBACK);

  // Attach an Interupt to digital pin 2 (interupt 0),
  attachInterrupt(0, handleZeroCrossInterrupt, RISING);

  // Initialize timer
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(handleTimerInterrupt, freqStep);
}

void loop()
{
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].update();
  }
}

// Functions
void handleTimerInterrupt() {
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].burn();
  }
}

void handleZeroCrossInterrupt()
{
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].zeroCrossed();
  }
}

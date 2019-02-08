/*
 Dim_PSSR_ZC_Tail

 This sketch is a sample sketch using the ZeroCross Tail(ZCT)to generate a sync
 pulse to drive a PowerSSR Tail(PSSRT) for dimming ac lights.

 Connections to an Arduino Duemilanove:
 1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm pull up to Arduino 5V.
 2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
 3. Connect the PowerSSR Tail +in terminal to digital pin 4 and the -in terminal to Gnd.


*/

#include <MIDI.h>
#include <TimerOne.h>
#include "PowerSSR.h"

int PSSR1 = 4;                  // PowerSSR Tail connected to digital pin 4
int PSSR2 = 5;                  // PowerSSR Tail connected to digital pin 5
int LED = 0;                    // LED on Arduino board on digital pin 13
const int NUM_SSRS = 2;

// Set to 60hz mains for now
int freqStep = 60;

volatile boolean isOn = 0;
volatile int speed = 100;
volatile int dim = 128;

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

PowerSSR ssrs[NUM_SSRS];

void setup()
{
  // Serial.begin(31250);
  pinMode(LED, OUTPUT);
  
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  MIDI.setHandleNoteOn(handleNoteOn); 
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].init(i + 4);
  }

  // Attach an Interupt to digital pin 2 (interupt 0),
  attachInterrupt(0, handleZeroCrossInterrupt, RISING);

  // Initialize timer
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(handleTimerInterrupt, freqStep);
}

void loop()
{
  // Continuously check if Midi data has been received.
  MIDI.read();
  
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

void handleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED, HIGH);
  
  if (isOn == 1) {
    ssrs[0].go(128, 250, LINEAR);
    ssrs[1].go(128, 250, LINEAR);
    isOn = 0;
  } else {
    isOn = 1;
    ssrs[0].go(20, 250, LINEAR);
    ssrs[1].go(20, 250, LINEAR);
  }
  
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
void handleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED, LOW);
  // ssrs[0].go(128, 500, LINEAR);
  // ssrs[1].go(128, 500, LINEAR);
}

void handleControlChange(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED, LOW);
  
  int vel = (int) velocity;
  // int val = map(vel, , 127, 0, 128);
  
  if (pitch == 0x07) {
    // dimmer
    dim = 128 - vel;
  }
  
  if (pitch == 0x1B) {
    // speed
    speed = (100 + 3000) - map(vel, 0, 127, 100, 3000);
  }
  
  ssrs[0].go(dim, speed, LINEAR);
  ssrs[1].go(dim, speed, LINEAR);
}

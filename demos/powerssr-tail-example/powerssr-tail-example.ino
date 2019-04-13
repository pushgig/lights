/*
 Dim_PSSR_ZC_Tail

 This sketch is a sample sketch using the ZeroCross Tail(ZCT)to generate a sync
 pulse to drive a PowerSSR Tail(PSSRT) for dimming ac lights.

 Connections to an Arduino Duemilanove:
 1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm pull up to Arduino 5V.
 2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
 3. Connect the PowerSSR Tail +in terminal to digital pin 4 and the -in terminal to Gnd.


*/
#define TIMELINE_SIZE 20

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MIDI.h>
#include <TimerOne.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "PulseAnimation.h"
#include "FloodAnimation.h"

int LED = 0;
byte LCD_ADDRESS = 0x27;

// 60hz AC mains
int AC_FREQUENCY = 60;

volatile int speed = 100;
volatile int dim = 128;
unsigned long currentMicros = 0;

// Create instance of LCD library
LiquidCrystal_I2C lcd(LCD_ADDRESS, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

// Create instances of SSRs
PowerSSR ssrs[NUM_SSRS];

// Create initial animation
PulseAnimation pulse(ssrs);
FloodAnimation flood(ssrs);

int animation = 1;

void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.clear();
  
  // TODO: perform a quick system check and 
  // only print FUCK YEAH if everything passes
  lcd.print("FUCK YEAH");
  
  pinMode(LED, OUTPUT);
  
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  MIDI.setHandleNoteOn(handleNoteOn); 
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleProgramChange(handleProgramChange);
  
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].init(i + 3);
  }

  // Attach an Interupt to digital pin 2 (interupt 0),
  attachInterrupt(0, handleZeroCrossInterrupt, RISING);

  // Initialize timer
  Timer1.initialize(AC_FREQUENCY);
  Timer1.attachInterrupt(handleTimerInterrupt, AC_FREQUENCY);
  
  SSRAnimation& anim = currentAnimation();

  // Tell the tween that time has changed and to adjust its calculations.
  anim.start();
}

void loop()
{
  // Continuously check if Midi data has been received.
  MIDI.read();
  
  SSRAnimation& anim = currentAnimation();
  anim.update(millis());
}

// Functions
SSRAnimation& currentAnimation() {
  switch(animation) {
    case 0:
      return flood;
    case 1:
    default:
      return pulse;
  }
}

void handleTimerInterrupt() {
  currentMicros = micros();
  
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].burn(currentMicros);
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
  
  lcd.clear();
  lcd.print("MIDI: Note On");
  lcd.setCursor(0, 1);
  lcd.print("Pitch: ");
  lcd.print(pitch);
  lcd.setCursor(0, 2);
  lcd.print("Velocity: ");
  lcd.print(velocity);
  
  int ssr = -1;
  
  // alesis pad
  // switch(pitch) {
  //   case 48:
  //     ssr = 0;
  //     break;
  //   case 45:
  //     ssr = 1;
  //     break;
  //   case 36:
  //     ssr = 2;
  //     break;
  //   case 38:
  //     ssr = 3;
  //     break;
  //   case 42:
  //     ssr = 4;
  //     break;
  // }
  
  // ableton
  switch(pitch) {
    case 96:
      ssr = 0;
      break;
    case 98:
      ssr = 1;
      break;
    case 100:
      ssr = 2;
      break;
    case 101:
      ssr = 3;
      break;
    case 103:
      ssr = 4;
      break;
    case 108:
      // C7: flood
      ssr = 10;
      break;
  }
  
  lcd.setCursor(0, 3);
  lcd.print("SSR: ");
  lcd.print(ssr);
  
  if (ssr == 10) {
    // flood
    for (int i = 0; i < NUM_SSRS; i++) {
      ssrs[i].go(128 - velocity);
    }
  } else if (ssr >= 0) {
    ssrs[ssr].go(128 - velocity);
  }
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
void handleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED, LOW);
  
  // lcd.clear();
  // lcd.print("MIDI: Note Off");
  // lcd.setCursor(0, 1);
  // lcd.print("Pitch: ");
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print("Velocity: ");
  // lcd.print(velocity);
  
  int ssr = -1;
  
  switch(pitch) {
    case 96:
      ssr = 0;
      break;
    case 98:
      ssr = 1;
      break;
    case 100:
      ssr = 2;
      break;
    case 101:
      ssr = 3;
      break;
    case 103:
      ssr = 4;
      break;
  }
  
  lcd.setCursor(0, 3);
  lcd.print("SSR: ");
  lcd.print(ssr);
  
  if (ssr >= 0) {
    ssrs[ssr].go(128);
  }
}

void handleControlChange(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED, LOW);
  
  lcd.clear();
  lcd.print("MIDI: Control Change");
  lcd.setCursor(0, 1);
  lcd.print("Pitch: ");
  lcd.print(pitch);
  lcd.setCursor(0, 2);
  lcd.print("Velocity: ");
  lcd.print(velocity);
  
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
  
  for (int i = 0; i < NUM_SSRS; i++) {
    ssrs[i].go(dim, speed, LINEAR);
  }
}

void handleProgramChange(byte channel, byte number) { 
  digitalWrite(LED, LOW);
  
  lcd.clear();
  lcd.print("MIDI: Program Change");
  lcd.setCursor(0, 1);
  lcd.print("Channel: ");
  lcd.print(channel);
  lcd.setCursor(0, 2);
  lcd.print("Number: ");
  lcd.print(number);
  
  switch(number) {
    case 10:
      animation = 0;
      break;
    case 11:
      animation = 1;
      break;
  }
  
  SSRAnimation& anim = currentAnimation();
  anim.start();
}

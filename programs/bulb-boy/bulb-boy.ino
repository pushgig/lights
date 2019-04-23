/*
 Bulb Boy 1.1
*/
#define TIMELINE_SIZE 20


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MIDI.h>
#include <TimerOne.h>
#include <MemoryFree.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "StopAnimation.h"
#include "FloodAnimation.h"
#include "PulseAnimation.h"
#include "DialAnimation.h"
#include "WaveAnimation.h"
#include "CandleAnimation.h"

byte LED = 0;
byte LCD_ADDRESS = 0x27;

// 60hz AC mains
byte AC_FREQUENCY = 60;

volatile byte speed = 100;
volatile byte intensity = MAX_BRIGHT;
unsigned long currentMicros = 0;

// Create instance of LCD library
LiquidCrystal_I2C lcd(LCD_ADDRESS, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

// Create instances of SSRs
PowerSSR ssrs[SSR_COUNT];

// Create initial animation
SSRAnimation* animation = new FloodAnimation(ssrs);

void setup()
{
  // Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.clear();
  
  // TODO: perform a quick system check and 
  // only print FUCK YEAH if everything passes
  lcd.print(F("FUCK YEAH"));
  
  pinMode(LED, OUTPUT);
  
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  MIDI.setHandleNoteOn(handleNoteOn); 
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleProgramChange(handleProgramChange);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    ssrs[i].init(i + 3);
  }

  // Attach an Interupt to digital pin 2 (interupt 0),
  attachInterrupt(0, handleZeroCrossInterrupt, RISING);

  // Initialize timer
  Timer1.initialize(AC_FREQUENCY);
  Timer1.attachInterrupt(handleTimerInterrupt, AC_FREQUENCY);
  
  // Tell the tween that time has changed and to adjust its calculations.
  startAnimation();
}

void loop()
{
  // Continuously check if Midi data has been received.
  MIDI.read();
  
  animation->update(millis());
}

// Functions
void handleTimerInterrupt() {
  currentMicros = micros();
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    ssrs[i].burn(currentMicros);
  }
}

void handleZeroCrossInterrupt()
{
  for (byte i = 0; i < SSR_COUNT; i++) {
    ssrs[i].zeroCrossed();
  }
}

void handleNoteOn(byte channel, byte pitch, byte velocity) { 
  // lcd.clear();
  // lcd.print("MIDI: Note On");
  // lcd.setCursor(0, 1);
  // lcd.print("Pitch: ");
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print("Velocity: ");
  // lcd.print(velocity);
  
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
  // switch(pitch) {
  //   case 96:
  //     ssr = 0;
  //     break;
  //   case 98:
  //     ssr = 1;
  //     break;
  //   case 100:
  //     ssr = 2;
  //     break;
  //   case 101:
  //     ssr = 3;
  //     break;
  //   case 103:
  //     ssr = 4;
  //     break;
  //   case 108:
  //     // C7: flood
  //     ssr = 10;
  //     break;
  // }
  
  // lcd.setCursor(0, 3);
  // lcd.print("SSR: ");
  // lcd.print(ssr);
  
  if (ssr == 10) {
    // flood
    for (byte i = 0; i < SSR_COUNT; i++) {
      ssrs[i].update(128 - velocity);
    }
  } else if (ssr >= 0) {
    ssrs[ssr].update(128 - velocity);
  }
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
void handleNoteOff(byte channel, byte pitch, byte velocity) { 
  // lcd.clear();
  // lcd.print("MIDI: Note Off");
  // lcd.setCursor(0, 1);
  // lcd.print("Pitch: ");
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print("Velocity: ");
  // lcd.print(velocity);
  
  int ssr = -1;
  
  // switch(pitch) {
  //   case 96:
  //     ssr = 0;
  //     break;
  //   case 98:
  //     ssr = 1;
  //     break;
  //   case 100:
  //     ssr = 2;
  //     break;
  //   case 101:
  //     ssr = 3;
  //     break;
  //   case 103:
  //     ssr = 4;
  //     break;
  // }
  
  // lcd.setCursor(0, 3);
  // lcd.print("SSR: ");
  // lcd.print(ssr);
  // 
  if (ssr >= 0) {
    ssrs[ssr].update(128);
  }
}

void handleControlChange(byte channel, byte pitch, byte velocity) { 
  // lcd.clear();
  // lcd.print("MIDI: Control Change");
  // lcd.setCursor(0, 1);
  // lcd.print("Pitch: ");
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print("Velocity: ");
  // lcd.print(velocity);
  
  // int vel = (int) velocity;
  // int val = map(vel, , 127, 0, 128);
  
  if (pitch == 0x07) {
    // dimmer
    intensity = 127 - velocity;
  }
  
  if (pitch == 0x1B) {
    // speed
    // speed = (100 + 3000) - map(vel, 0, 127, 100, 3000);
    speed = 127 - velocity;
  }
  
  animation->speed(speed);
  animation->intensity(intensity);
}

void startAnimation() {
  animation->speed(speed);
  animation->intensity(intensity);
  animation->start(millis());
}

void handleProgramChange(byte channel, byte program) { 
  digitalWrite(LED, LOW);
  
  lcd.clear();
  // lcd.print("MIDI: Program Change");
  // 
  // lcd.print("Channel: ");
  // lcd.print(channel);
  // lcd.setCursor(0, 2);
  // lcd.print("Number: ");
  // lcd.print(number);
  
  byte number = program % 10;

  lcd.setCursor(0, 1);
  lcd.print(F("ANIMATION: "));
  lcd.print(number);
  
  // stop current animation
  animation->stop();
  delete animation;
  animation = nullptr;
  
  switch(number) {
    // case 0:
    default:
      animation = new StopAnimation(ssrs);
      break;
    case 1:
      animation = new FloodAnimation(ssrs);
      break;
    case 2:
      animation = new PulseAnimation(ssrs);
      break;
    case 3:
      animation = new DialAnimation(ssrs);
      break;
    case 4:
      animation = new CandleAnimation(ssrs);
      break;
    case 5:
      animation = new WaveAnimation(ssrs);
      break;
  }
  
  startAnimation();
  
  lcd.setCursor(0, 0);
  lcd.print(F("FREE MEMORY: "));
  lcd.print(freeMemory());
}

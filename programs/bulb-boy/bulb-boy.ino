/*
 Bulb Boy 1.1
*/
#define TIMELINE_SIZE 10

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
#include "RainAnimation.h"

byte LED = 0;
byte LCD_ADDRESS = 0x27;

// TODO: make intensity and speed based on NOTE ON octave & velocity
volatile byte speed = 100;
volatile byte intensity = MAX_BRIGHT;
unsigned long currentMicros = 0;

// Create instance of LCD library
LiquidCrystal_I2C lcd(LCD_ADDRESS, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Create an instance of the MIDI library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

// Create instances of SSRs
PowerSSR ssrs[SSR_COUNT];

// Create initial animation
SSRAnimation* animation = new StopAnimation(ssrs);

void setup()
{
  // Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.clear();
  
  // TODO: perform a quick system check and 
  // only print FUCK YEAH if everything passes
  lcd.print(F("FUCK YEAH"));
  
  pinMode(LED, OUTPUT);
  
  // OMNI sets it to listen to all channels. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  MIDI.setHandleNoteOn(handleNoteOn); 
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleProgramChange(handleProgramChange);
  
  // initialize SSRs on pins 3 - n
  for (byte i = 0; i < SSR_COUNT; i++) {
    ssrs[i].init(i + 3);
  }

  // attach an Interupt to digital pin 2 (interupt 0),
  attachInterrupt(0, handleZeroCrossInterrupt, RISING);

  // initialize timer
  Timer1.initialize(AC_FREQUENCY);
  Timer1.attachInterrupt(handleTimerInterrupt, AC_FREQUENCY);
  
  // start the first animation
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
  // lcd.print(F("MIDI: Note On"));
  // lcd.setCursor(0, 1);
  // lcd.print(F("Pitch: "));
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print(F("Velocity: "));
  // lcd.print(velocity);
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
void handleNoteOff(byte channel, byte pitch, byte velocity) { 
  // lcd.clear();
  // lcd.print(F("MIDI: Note Off"));
  // lcd.setCursor(0, 1);
  // lcd.print(F("Pitch: "));
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print(F("Velocity: "));
  // lcd.print(velocity);
}

void handleControlChange(byte channel, byte pitch, byte velocity) { 
  // lcd.clear();
  // lcd.print(F("MIDI: Control Change"));
  // lcd.setCursor(0, 1);
  // lcd.print(F("Pitch: "));
  // lcd.print(pitch);
  // lcd.setCursor(0, 2);
  // lcd.print(F("Velocity: "));
  // lcd.print(velocity);
  
  if (pitch == 0x07) {
    intensity = 127 - velocity;
  }

  if (pitch == 0x1B) {
    speed = 127 - velocity;
  }
}

void startAnimation() {
  animation->speed(speed);
  animation->intensity(intensity);
  animation->start(millis());
}

void handleProgramChange(byte channel, byte program) { 
  digitalWrite(LED, LOW);
  
  byte number = program % 10;
  
  // stop current animation
  animation->stop();
  animation->destroy();
  delete animation;
  animation = nullptr;
  
  switch(number) {
    case 0:
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
    case 6:
      animation = new RainAnimation(ssrs);
      break;
  }
  
  startAnimation();
  
  lcd.clear();
  lcd.print(F("MIDI: Program Change"));
  lcd.setCursor(0, 1);
  lcd.print(F("CHN: "));
  lcd.print(channel);
  lcd.print(F(" PRG: "));
  lcd.print(program);
  lcd.setCursor(0, 2);
  lcd.print(F("PTN: "));
  lcd.print(number);
  lcd.print(F(" MEM: "));
  lcd.print(freeMemory());
}


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED 13

#include <MIDI.h>

// struct HairlessSettings : public midi::DefaultSettings
// {
//    static const bool BaudRate = 115200;
// };

// MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, midiIn, HairlessSettings);

// Parameter 1 = number of pixels in strip1
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(60, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(60, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(60, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// 
// void HandleNoteOff (byte channel, byte note, byte velocity)
// void HandleAfterTouchPoly (byte channel, byte note, byte pressure)
// void HandleControlChange (byte channel, byte number, byte value)
// void HandleProgramChange (byte channel, byte number)
// void HandleAfterTouchChannel (byte channel, byte pressure)
// void HandlePitchBend (byte channel, int bend)
// void HandleSystemExclusive (byte *array, byte size)
// void HandleTimeCodeQuarterFrame (byte data)
// void HandleSongPosition (unsigned int beats)
// void HandleSongSelect (byte songnumber)
// void HandleTuneRequest (void)
// void HandleClock (void)
// void HandleStart (void)
// void HandleContinue (void)
// void HandleStop (void)
// void HandleActiveSensing (void)
// void HandleSystemReset (void)

uint32_t magenta = strip1.Color(255, 0, 255);
uint32_t blue = strip1.Color(0, 0, 255);
uint32_t green = strip1.Color(0, 255, 0);
uint32_t red = strip1.Color(255, 0, 0);
uint32_t purple = strip1.Color(148, 0, 211);
uint32_t orange = strip1.Color(255, 165, 0);
uint32_t yellow = strip1.Color(255, 255, 0);
uint32_t off = strip1.Color(0, 0, 0);

// uint32_t getColor(byte note) {
//   switch (note) {
//     case 36: return magenta;
//     case 38: return blue;
//     case 42: return green;
//     case 45: return orange;
//     case 46: return red;
//     case 48: return yellow;
//     case 49: return purple;
//     case 51:
//     default: return off;
//   }
// }

// void HandleNoteOn (byte channel, byte note, byte velocity) {
//     uint32_t color = getColor(note);

//     colorWipeCount(velocity / 4, color, 1);
// }


void setup() {
  // midiIn.begin();
  // midiIn.turnThruOff();
  // midiIn.setHandleNoteOn(HandleNoteOn);

  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();

  colorWipe(strip1, blue, 64);
  colorWipe(strip2, green, 32);
  colorWipe(strip3, purple, 16);
  colorWipe(strip4, orange, 8);
  colorWipe(strip5, magenta, 4);

}

// uint32_t r = random(0, 255);
// uint32_t g = random(0, 255);
// uint32_t b = random(0, 255);

// uint32_t i = 0;

void loop() {
  // colorWipe(strip1, off, 2);
  // colorWipe(strip2, off, 2);
  // colorWipe(strip3, off, 2);
  // colorWipe(strip4, off, 2);
  // colorWipe(strip5, off, 2);

  // colorWipe(strip1, magenta, 2);
  // colorWipe(strip2, blue, 2);
  // colorWipe(strip3, green, 2);
  // colorWipe(strip4, orange, 2);
  // colorWipe(strip5, red, 2);

}

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


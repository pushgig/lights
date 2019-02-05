#include <MIDI.h>

struct HairlessSettings : public midi::DefaultSettings
{
   static const bool BaudRate = 38400;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, midiIn, HairlessSettings);

// This example shows the old way of checking for input messages.
// It's simpler to use the callbacks now, check out the dedicated example.
#define LED 13                   // LED pin on Arduino Uno
// -----------------------------------------------------------------------------
void BlinkLed(byte num)         // Basic blink function
{
    for (byte i=0;i<num;i++)
    {
        digitalWrite(LED,HIGH);
        delay(50);
        digitalWrite(LED,LOW);
        delay(50);
    }
}
// -----------------------------------------------------------------------------
void setup()
{
    pinMode(LED, OUTPUT);
    midiIn.begin();           // Launch MIDI, by default listening to channel 1.
}
void loop()
{
    if (midiIn.read())                // Is there a MIDI message incoming ?
    {
      BlinkLed(5);  // blink the LED a number of times
    }
}
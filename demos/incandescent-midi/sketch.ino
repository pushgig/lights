#include <MIDI.h>  // Add Midi Library

#define LED 13    // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Set Arduino board pin 13 to output
  pinMode (LED, OUTPUT);
  
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  MIDI.setHandleNoteOn(handleNoteOn); 
  MIDI.setHandleNoteOff(handleNoteOff);
}

// Main loop
void loop() { 
  MIDI.read(); // Continuously check if Midi data has been received.
}

void handleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,HIGH);  //Turn LED on
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
void handleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,LOW);  //Turn LED off
}

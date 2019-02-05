#include <MIDI.h>  // Add Midi Library
#include <Ramp.h> // Add RAMP library

#define LED 13    // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

// Create a Ramp instance for each light so we can transition values smoothly
ramp ramps[5];

// map (interpolate) floating values
// double mapf(double x, double in_min, double in_max, double out_min, double out_max)
// {
//     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

void setup() {
  // Set Arduino board pin 13 to output
  pinMode (LED, OUTPUT);
  
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  MIDI.setHandleNoteOn(handleNoteOn); 
  MIDI.setHandleNoteOff(handleNoteOff);
  
  Serial.begin(9600);
  
  Serial.print("Value start at: ");
  Serial.println(ramps[0].value());

  Serial.print("Strating interpolation");
  
  // start interpolation (value to go to, duration)
  ramps[0].go(0, 0);                
}

// Main loop
void loop() { 
  MIDI.read(); // Continuously check if Midi data has been received.
}

void handleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,HIGH);  //Turn LED on
  ramps[0].go(velocity, 1000);
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
void handleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,LOW);  //Turn LED off
}

/*
  PowerSSR.cpp
*/

#include "Arduino.h"
#include "PowerSSR.h"

PowerSSR::PowerSSR()
{

}

void PowerSSR::init(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  
  // Default dimming level (0-127)  0 = on, 127 = off
  _dim = 127;
  _dimCount = 0;
  _zeroCrossed = 0;
  _previousMicros = 0;
  _isBurning = 0;
}

void PowerSSR::update(int brightness) {
  _dim = 127 - constrain(brightness, 0, 127);
}

void PowerSSR::zeroCrossed()
{
  _zeroCrossed = 1;
}

void PowerSSR::burn(unsigned long currentMicros)
{
  if (currentMicros < _previousMicros) {
    // micros() will overflow (go back to zero) after around 70 minutes
    _previousMicros = currentMicros;
  }
  
  if(_zeroCrossed == 1) {
    if(_dimCount >= _dim) {
      if (_isBurning == 0 && currentMicros - _previousMicros >= 100) {
        digitalWrite(_pin, HIGH);
        _previousMicros = currentMicros;
        _isBurning = 1;
      }
      
      if (_isBurning == 1 && currentMicros - _previousMicros >= 50) {
        digitalWrite(_pin, LOW);
        _isBurning = 0;
        _zeroCrossed = 0;
        _dimCount = 0;
      }
    } else {
      _dimCount++;
    }
  }
}
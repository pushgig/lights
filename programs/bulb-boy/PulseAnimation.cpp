/*
  PulseAnimation.cpp
*/

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "PulseAnimation.h"

PulseAnimation::PulseAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  
}

void PulseAnimation::start(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].value = LIGHT_MIN;
    _ssrs[i].timeline.addTo(_ssrs[i].value, LIGHT_MED, 5000);
    _ssrs[i].timeline.addTo(_ssrs[i].value, LIGHT_MIN, 5000);
    _ssrs[i].timeline.begin(millis);
    _ssrs[i].timeline.restartFrom(millis);
  }
}

void PulseAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    _ssrs[i].update(_ssrs[i].value);
    
    if (_ssrs[i].timeline.isComplete()) {
      _ssrs[i].timeline.restartFrom(millis);
    }
  }
}

void PulseAnimation::bump(uint32_t millis) {

}

void PulseAnimation::stop() {

}
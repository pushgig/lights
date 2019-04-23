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
    _ssrs[i].value = MIN_BRIGHT;
    _ssrs[i].timeline.addTo(_ssrs[i].value, 80, 5000);
    _ssrs[i].timeline.addTo(_ssrs[i].value, 120, 5000);
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

void PulseAnimation::stop() {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.wipe();
  }
}
/*
  FloodAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "FloodAnimation.h"

FloodAnimation::FloodAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{

}

void FloodAnimation::start(uint32_t millis) {
  byte brightness = map(_intensity, 0, 127, LIGHT_MED, LIGHT_MAX);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].value = brightness - 50;
    _ssrs[i].timeline.addTo(_ssrs[i].value, brightness, 250);
    _ssrs[i].timeline.begin(millis);
  }
}

void FloodAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    _ssrs[i].update(_ssrs[i].value);
    
    if (_ssrs[i].timeline.isComplete()) {
      _ssrs[i].timeline.restartFrom(millis);
    }
  }
}

void FloodAnimation::bump(uint32_t millis) {
  
}

void FloodAnimation::stop() {
  
}
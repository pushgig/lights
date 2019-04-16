/*
  PulseAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "Config.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "PulseAnimation.h"

PulseAnimation::PulseAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  _value = MIN_BRIGHT;
  
  timeline.addTo(_value, 80, 5000);
  timeline.addTo(_value, 120, 5000);
}

void PulseAnimation::start(uint32_t millis) {
  // nothing here
  _value = MIN_BRIGHT;
  timeline.restartFrom(millis);
}

void PulseAnimation::update(uint32_t millis) {
  timeline.update(millis);
  
  for (byte i = 0; i < NUM_SSRS; i++) {
    // update with new tween value
    _ssrs[i].update(_value);
  }
  
  // Restart the loop if we're finished!
  if (timeline.isComplete()) {
    timeline.restartFrom(millis);
  }
}
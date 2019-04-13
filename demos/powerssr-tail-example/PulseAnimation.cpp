/*
  PulseAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "PulseAnimation.h"

PulseAnimation::PulseAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  _value = 127;
  
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUAD;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;
  
  timeline.addTo(_value, 60, 2000, ease, easeType);
  timeline.addTo(_value, 120, 2000, ease, easeType);
}

void PulseAnimation::start() {
  // nothing here
  _value = 127;
  timeline.restartFrom(millis());
}

void PulseAnimation::update(uint32_t millis) {
  timeline.update(millis);
  int dim = round(_value);
  
  for (int i = 0; i < NUM_SSRS; i++) {
    // update with new tween value
    _ssrs[i].update(dim);
  }
  
  // Restart the loop if we're finished!
  if (timeline.isComplete()) {
    timeline.restartFrom(millis);
  }
}
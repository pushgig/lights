/*
  WaveAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "WaveAnimation.h"

WaveAnimation::WaveAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  _value = 127;
  
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUAD;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;
  
  timeline.addTo(_value, 80, 5000);
  timeline.addTo(_value, 120, 5000);
}

void WaveAnimation::begin(uint32_t millis) {
  // nothing here
  _value = 127;
  timeline.restartFrom(millis);
}

void WaveAnimation::update(uint32_t millis) {
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
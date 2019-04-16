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
  _value = 127;
  
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUAD;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;
  
  tween = TweenDuino::Tween::to(_value, 500, 0, ease, easeType);
}

void FloodAnimation::begin(uint32_t millis) {
  // nothing here
  _value = 127;
  tween->restartFrom(millis);
}

void FloodAnimation::update(uint32_t millis) {
  tween->update(millis);
  int dim = round(_value);
  
  for (int i = 0; i < NUM_SSRS; i++) {
    // update with new tween value
    _ssrs[i].update(dim);
  }
}
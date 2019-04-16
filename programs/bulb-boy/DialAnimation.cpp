/*
  DialAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "DialAnimation.h"

DialAnimation::DialAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  _count = 0;
  _value = 127;
  
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUAD;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;
  
  tween = TweenDuino::Tween::to(_value, 1000, 127, ease, easeType);
}

void DialAnimation::begin(uint32_t millis) {
  // nothing here
  _value = 0;
  _count = _count + 1;
  tween->restartFrom(millis);
}

void DialAnimation::update(uint32_t millis) {
  tween->update(millis);
  int dim = round(_value);
  
  for (int i = 0; i < NUM_SSRS; i++) {
    // update with new tween value
    if (_count % 2 == i % 2) {
      _ssrs[i].update(dim);
    } else {
      _ssrs[i].update(127);
    }
  }
}
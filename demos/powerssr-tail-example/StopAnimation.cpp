/*
  StopAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "StopAnimation.h"

StopAnimation::StopAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  // _value = 127;
  // 
  // TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUAD;
  // TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;
  // 
  // tween = TweenDuino::Tween::to(_value, 500, 127, ease, easeType);
}

void StopAnimation::begin(uint32_t millis) {
  for (int i = 0; i < NUM_SSRS; i++) {
    // update with new tween value
    _ssrs[i].update(127);
  }
}

void StopAnimation::update(uint32_t millis) {
  // nothing here
}
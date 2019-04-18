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
  // _value = MIN_BRIGHT;
  
  // TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUAD;
  // TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;
  // 
  // tween = TweenDuino::Tween::to(_value, 500, MAX_BRIGHT, ease, easeType);
}

void FloodAnimation::start(uint32_t millis) {
  // nothing here
  // _value = MAX_BRIGHT;
  // tween->restartFrom(millis);
}

void FloodAnimation::update(uint32_t millis) {
  // tween->update(millis);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    // update with new tween value
    _ssrs[i].update(_intensity);
  }
}

void FloodAnimation::stop() {
  // nothing here
}
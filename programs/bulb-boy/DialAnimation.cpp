/*
  DialAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "Config.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "DialAnimation.h"

DialAnimation::DialAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  _count = 0;
  _value = MIN_BRIGHT;
  
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::CUBIC;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::IN;
  
  tween = TweenDuino::Tween::to(_value, 750, MIN_BRIGHT, ease, easeType);
}

void DialAnimation::start(uint32_t millis) {
  // nothing here
  _value = MAX_BRIGHT;
  _count = _count + 1;
  tween->restartFrom(millis);
}

void DialAnimation::update(uint32_t millis) {
  tween->update(millis);
  for (byte i = 0; i < NUM_SSRS; i++) {
    // update with new tween value
    if (_count % 2 == i % 2) {
      _ssrs[i].update(_value);
    } else {
      _ssrs[i].update(MIN_BRIGHT);
    }
  }
}
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
  canBump = 1;
  _count = 0;
}

void DialAnimation::start(uint32_t millis) {
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::CUBIC;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::OUT;

  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].value = MIN_BRIGHT;
    _ssrs[i].timeline.addTo(_ssrs[i].value, map(_intensity, 0, 127, MAX_BRIGHT, 80), 100);
    _ssrs[i].timeline.addTo(_ssrs[i].value, MIN_BRIGHT, map(_speed, 0, 127, 600, 1200), ease, easeType);
  }
}

void DialAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    _ssrs[i].update(_ssrs[i].value);
    
    if (_count % 2 == i % 2) {
      _ssrs[i].timeline.restartFrom(millis);
    } else {
      _ssrs[i].value = MIN_BRIGHT;
    }
  }
}

void DialAnimation::bump(uint32_t millis) {
  _count = _count + 1;
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    if (_count % 2 == i % 2) {
      _ssrs[i].timeline.restartFrom(millis);
    } else {
      _ssrs[i].value = MIN_BRIGHT;
    }
  }
}

void DialAnimation::stop() {
  
}
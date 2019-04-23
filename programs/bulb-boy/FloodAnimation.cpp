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
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUINT;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::IN;

  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].value = map(_intensity, 0, 127, MAX_BRIGHT, 80);
    _ssrs[i].timeline.addTo(_ssrs[i].value, MIN_BRIGHT, map(_speed, 0, 127, 1200, 2400), ease, easeType);
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

void FloodAnimation::stop() {
  
}
/*
  HitAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "HitAnimation.h"

HitAnimation::HitAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{

}

void HitAnimation::start(uint32_t millis) {
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUINT;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::IN;
  
  byte startBrightness = map(_intensity, 0, 127, LIGHT_MED, LIGHT_MAX);
  byte endBrightness = max(startBrightness - 50, LIGHT_MIN);
  unsigned short int duration = map(_speed, 0, 127, 1000, 600);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].value = startBrightness;
    _ssrs[i].timeline.addTo(_ssrs[i].value, endBrightness, duration, ease, easeType);
    _ssrs[i].timeline.begin(millis);
  }
}

void HitAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    _ssrs[i].update(_ssrs[i].value);
  }
}

void HitAnimation::bump(uint32_t millis) {
  
}

void HitAnimation::stop() {
  
}
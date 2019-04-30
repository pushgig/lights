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
  TweenDuino::Tween::Ease ease = TweenDuino::Tween::Ease::QUINT;
  TweenDuino::Tween::EaseType easeType = TweenDuino::Tween::EaseType::IN;

  unsigned short int duration = map(_speed, 0, 127, 400, 200);
  byte brightness = map(_intensity, 0, 127, LIGHT_MED, LIGHT_MAX);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.addTo(_ssrs[i].value, brightness - 40, duration, ease, easeType);
  }
}

void DialAnimation::update(uint32_t millis) {
  byte brightness = map(_intensity, 0, 127, LIGHT_MED, LIGHT_MAX);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    
    if (_count % 2 == i % 2) {
      _ssrs[i].value = brightness;
    } 
    
    _ssrs[i].update(_ssrs[i].value);
  }
}

void DialAnimation::bump(uint32_t millis) {
  _count = _count + 1;
  
  SSRAnimation::destroy();
  start(millis);
}

void DialAnimation::stop() {
  
}
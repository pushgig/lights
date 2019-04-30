/*
  CandleAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "CandleAnimation.h"

CandleAnimation::CandleAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
}

void CandleAnimation::start(uint32_t millis) {

}

void CandleAnimation::update(uint32_t millis) {
  // speed is inverse to delay
  unsigned short int delay = map(_speed, 0, 127, 500, 10);
  
  if (millis % delay == 0) {
    for (byte i = 0; i < SSR_COUNT; i++) {
      byte brightness = map(_intensity, 0, 127, LIGHT_MIN, LIGHT_MED) + random(0, 30);
      _ssrs[i].update(brightness);
    }
  }
}

void CandleAnimation::bump(uint32_t millis) {

}

void CandleAnimation::stop() {

}
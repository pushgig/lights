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
  if (millis % map(_speed, 0, 127, 10, 500) == 0) {
    for (byte i = 0; i < SSR_COUNT; i++) {
      _ssrs[i].update(map(_intensity, 0, 127, 60, 90) + random(0, 30));
    }
  }
}

void CandleAnimation::stop() {

}
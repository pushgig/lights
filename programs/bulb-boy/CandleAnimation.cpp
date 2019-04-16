/*
  CandleAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "Config.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "CandleAnimation.h"

CandleAnimation::CandleAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
}

void CandleAnimation::start(uint32_t millis) {
  // nothing here
}

void CandleAnimation::update(uint32_t millis) {
  if (millis % map(_speed, 0, 127, 10, 250) == 0) {
    for (byte i = 0; i < NUM_SSRS; i++) {
      // update with new tween value
      _ssrs[i].update(map(_intensity, 0, 127, 60, 100) + random(0, 20));
    }
  }
}

void CandleAnimation::stop() {
  // nothing here
}
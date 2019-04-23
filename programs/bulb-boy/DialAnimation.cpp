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
  _count = 0;
}

void DialAnimation::start(uint32_t millis) {
  _count = _count + 1;
}

void DialAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    if (_count % 2 == i % 2) {
      _ssrs[i].update(_intensity);
    } else {
      _ssrs[i].update(MIN_BRIGHT);
    }
  }
}

void DialAnimation::stop() {
  // nothing here
}
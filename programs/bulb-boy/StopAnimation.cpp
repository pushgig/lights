/*
  StopAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "StopAnimation.h"

StopAnimation::StopAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  // nothing here
}

void StopAnimation::start(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    // update with new tween value
    _ssrs[i].update(MIN_BRIGHT);
  }
}

void StopAnimation::update(uint32_t millis) {
  // nothing here
}

void StopAnimation::stop() {
  // nothing here
}
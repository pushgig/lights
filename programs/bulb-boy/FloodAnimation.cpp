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

}

void FloodAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].update(map(_intensity, 0, 127, 30, 80));
  }
}

void FloodAnimation::stop() {

}
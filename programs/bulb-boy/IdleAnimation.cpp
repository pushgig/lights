/*
  IdleAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "IdleAnimation.h"

IdleAnimation::IdleAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{

}

void IdleAnimation::start(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].update(LIGHT_MIN);
  }
}

void IdleAnimation::update(uint32_t millis) {

}

void IdleAnimation::bump(uint32_t millis) {
  
}

void IdleAnimation::stop() {

}
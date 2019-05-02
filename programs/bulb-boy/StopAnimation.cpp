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

}

void StopAnimation::start(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].value = LIGHT_OFF;
    _ssrs[i].update(LIGHT_OFF);
  }
}

void StopAnimation::update(uint32_t millis) {

}

void StopAnimation::bump(uint32_t millis) {
  
}

void StopAnimation::stop() {

}
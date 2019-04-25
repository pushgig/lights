/*
  RainAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "RainAnimation.h"

RainAnimation::RainAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
}

void RainAnimation::start(uint32_t millis) {
  byte intensity = map(_intensity, 0, 127, 40, 90);
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.addTo(_ssrs[i].value, intensity, 50);
    _ssrs[i].timeline.addTo(_ssrs[i].value, intensity + 30, 1000);
  }
}

void RainAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    _ssrs[i].update(_ssrs[i].value);
    
    if (millis % map(_speed, 0, 127, 600, 600 + random(0, 400)) == 0) {
        _ssrs[random(0, SSR_COUNT)].timeline.restartFrom(millis);
    }
  }
}

void RainAnimation::bump(uint32_t millis) {

}

void RainAnimation::stop() {

}
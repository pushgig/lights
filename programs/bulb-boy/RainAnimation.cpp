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
  byte intensity = map(_intensity, 0, 127, LIGHT_MED, LIGHT_MAX);
  byte depth = 30;
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.addTo(_ssrs[i].value, intensity, 50);
    _ssrs[i].timeline.addTo(_ssrs[i].value, intensity - depth, 1000);
  }
}

void RainAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    _ssrs[i].update(_ssrs[i].value);
    
    unsigned short int delay = map(_speed, 0, 127, 600 + random(0, 400), 600);
    
    if (millis % delay == 0) {
        _ssrs[random(0, SSR_COUNT)].timeline.restartFrom(millis);
    }
  }
}

void RainAnimation::bump(uint32_t millis) {

}

void RainAnimation::stop() {

}
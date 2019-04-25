/*
  WaveAnimation.cpp
*/

#include "Arduino.h"
#include <TweenDuino.h>
#include "PowerSSR.h"
#include "SSRAnimation.h"
#include "WaveAnimation.h"

WaveAnimation::WaveAnimation(PowerSSR* ssrs) : SSRAnimation(ssrs)
{
  
}

void WaveAnimation::start(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.addTo(_ssrs[i].value, 80, 1000);
    _ssrs[i].timeline.addTo(_ssrs[i].value, 120, 1000);
    _ssrs[i].timeline.begin(millis);
    _ssrs[i].timeline.restartFrom(millis - (i * 250));
  }
}

void WaveAnimation::update(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    _ssrs[i].timeline.update(millis);
    // update with new tween value
    _ssrs[i].update(_ssrs[i].value);
    
    // Restart the loop if we're finished!
    if (_ssrs[i].timeline.isComplete()) {
      _ssrs[i].timeline.restartFrom(millis);
    }
  }
}

void WaveAnimation::bump(uint32_t millis) {

}

void WaveAnimation::stop() {

}

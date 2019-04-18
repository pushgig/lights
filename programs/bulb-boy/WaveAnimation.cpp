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
  for (byte i = 0; i < SSR_COUNT; i++) {
    _values[i] = MIN_BRIGHT;
    
    timelines[i].addTo(_values[i], 80, 1000);
    timelines[i].addTo(_values[i], 120, 1000);
  }
}

void WaveAnimation::start(uint32_t millis) {
  for (byte i = 0; i < SSR_COUNT; i++) {
    timelines[i].begin(millis);
    timelines[i].restartFrom(millis - (i * 250));
  }
}

void WaveAnimation::update(uint32_t millis) {
  
  for (byte i = 0; i < SSR_COUNT; i++) {
    timelines[i].update(millis);
    // update with new tween value
    _ssrs[i].update(_values[i]);
    
    // Restart the loop if we're finished!
    if (timelines[i].isComplete()) {
      timelines[i].restartFrom(millis);
    }
  }
}

void WaveAnimation::stop() {

}

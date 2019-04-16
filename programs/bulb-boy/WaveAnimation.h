/*
  WaveAnimation.h
*/
#ifndef WaveAnimation_h
#define WaveAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class WaveAnimation : public SSRAnimation
{
  public:
    WaveAnimation(PowerSSR* ssrs);
    virtual ~WaveAnimation(){}
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void stop();
  private:
    TweenDuino::Timeline timelines[NUM_SSRS];
    float _values[NUM_SSRS];
};

#endif
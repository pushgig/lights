/*
  PulseAnimation.h
*/
#ifndef PulseAnimation_h
#define PulseAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class PulseAnimation : public SSRAnimation
{
  public:
    PulseAnimation(PowerSSR* ssrs);
    virtual ~PulseAnimation(){}
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
  private:
    TweenDuino::Timeline timeline;
    float _value;
};

#endif
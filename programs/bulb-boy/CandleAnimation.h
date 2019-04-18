/*
  CandleAnimation.h
*/
#ifndef CandleAnimation_h
#define CandleAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class CandleAnimation : public SSRAnimation
{
  public:
    CandleAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void stop();
};

#endif
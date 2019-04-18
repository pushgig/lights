/*
  StopAnimation.h
*/
#ifndef StopAnimation_h
#define StopAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class StopAnimation : public SSRAnimation
{
  public:
    StopAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void stop();
};

#endif
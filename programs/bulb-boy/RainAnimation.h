/*
  RainAnimation.h
*/
#ifndef RainAnimation_h
#define RainAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

class RainAnimation : public SSRAnimation
{
  public:
    RainAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void bump(uint32_t millis);
    virtual void stop();
};

#endif
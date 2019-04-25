/*
  PulseAnimation.h
*/
#ifndef PulseAnimation_h
#define PulseAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

class PulseAnimation : public SSRAnimation
{
  public:
    PulseAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void bump(uint32_t millis);
    virtual void stop();
};

#endif
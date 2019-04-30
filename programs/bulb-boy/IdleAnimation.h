/*
  IdleAnimation.h
*/
#ifndef IdleAnimation_h
#define IdleAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

class IdleAnimation : public SSRAnimation
{
  public:
    IdleAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void bump(uint32_t millis);
    virtual void stop();
};

#endif
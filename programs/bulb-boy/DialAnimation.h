/*
  DialAnimation.h
*/
#ifndef DialAnimation_h
#define DialAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

class DialAnimation : public SSRAnimation
{
  public:
    DialAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void bump(uint32_t millis);
    virtual void stop();
  private:
    byte _count;
};

#endif
/*
  SSRAnimation.h
*/
#ifndef SSRAnimation_h
#define SSRAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"

class SSRAnimation
{
  public:
    SSRAnimation(PowerSSR* ssrs) { 
      _ssrs = ssrs;
    }
    virtual ~SSRAnimation(){}
    virtual void begin(uint32_t millis) = 0;
    virtual void update(uint32_t millis) = 0;
  protected:
    PowerSSR* _ssrs;
};

#endif
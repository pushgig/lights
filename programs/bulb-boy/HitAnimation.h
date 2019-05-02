/*
  HitAnimation.h
*/
#ifndef HitAnimation_h
#define HitAnimation_h

#include "PowerSSR.h"
#include "SSRAnimation.h"

class HitAnimation : public SSRAnimation
{
  public:
    HitAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void bump(uint32_t millis);
    virtual void stop();
};

#endif
/*
  FloodAnimation.h
*/
#ifndef FloodAnimation_h
#define FloodAnimation_h

#include "PowerSSR.h"
#include "SSRAnimation.h"

class FloodAnimation : public SSRAnimation
{
  public:
    FloodAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void bump(uint32_t millis);
    virtual void stop();
};

#endif
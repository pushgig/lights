/*
  WaveAnimation.h
*/
#ifndef WaveAnimation_h
#define WaveAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

class WaveAnimation : public SSRAnimation
{
  public:
    WaveAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void stop();
};

#endif
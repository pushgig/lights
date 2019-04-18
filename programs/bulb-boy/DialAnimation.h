/*
  DialAnimation.h
*/
#ifndef DialAnimation_h
#define DialAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class DialAnimation : public SSRAnimation
{
  public:
    DialAnimation(PowerSSR* ssrs);
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
    virtual void stop();
  private:
    // TweenDuino::Tween *tween;
    byte _count;
    float _value;
};

#endif
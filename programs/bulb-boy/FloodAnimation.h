/*
  FloodAnimation.h
*/
#ifndef FloodAnimation_h
#define FloodAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class FloodAnimation : public SSRAnimation
{
  public:
    FloodAnimation(PowerSSR* ssrs);
    virtual ~FloodAnimation(){}
    virtual void start(uint32_t millis);
    virtual void update(uint32_t millis);
  private:
    // TweenDuino::Tween *tween;
    // float _value;
};

#endif
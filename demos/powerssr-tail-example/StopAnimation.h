/*
  StopAnimation.h
*/
#ifndef StopAnimation_h
#define StopAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class StopAnimation : public SSRAnimation
{
  public:
    StopAnimation(PowerSSR* ssrs);
    virtual ~StopAnimation(){}
    virtual void begin(uint32_t millis);
    virtual void update(uint32_t millis);
  private:
    TweenDuino::Tween *tween;
    float _value;
};

#endif
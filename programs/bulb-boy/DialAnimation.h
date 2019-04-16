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
    virtual ~DialAnimation(){}
    virtual void begin(uint32_t millis);
    virtual void update(uint32_t millis);
  private:
    TweenDuino::Tween *tween;
    int _count;
    float _value;
};

#endif
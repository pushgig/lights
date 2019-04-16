/*
  WaveAnimation.h
*/
#ifndef WaveAnimation_h
#define WaveAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"
#include "SSRAnimation.h"

#include <TweenDuino.h>

class WaveAnimation : public SSRAnimation
{
  public:
    WaveAnimation(PowerSSR* ssrs);
    virtual ~WaveAnimation(){}
    virtual void begin(uint32_t millis);
    virtual void update(uint32_t millis);
  private:
    TweenDuino::Timeline timeline;
    float _value;
};

#endif
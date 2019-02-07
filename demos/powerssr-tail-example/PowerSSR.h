/*
  PowerSSR.h
*/
#ifndef PowerSSR_h
#define PowerSSR_h

#include "Arduino.h"
#include <Ramp.h>

class PowerSSR
{
  public:
    PowerSSR();
    void init(int pint);
    ramp value;
    void go(int, unsigned long, ramp_mode, loop_mode);
    void update();
    void zeroCrossed();
    void burn();
  private:
    int _pin;
    volatile boolean _zeroCrossed;
    int _dim;
    int _dimCount;
};

#endif
/*
  PowerSSR.h
*/
#ifndef PowerSSR_h
#define PowerSSR_h

#define NUM_SSRS 5

#include "Arduino.h"
#include <Ramp.h>

class PowerSSR
{
  public:
    PowerSSR();
    void init(int pint);
    ramp value;
    void go(int);
    void go(int, unsigned long);
    void go(int, unsigned long, ramp_mode);
    void go(int, unsigned long, ramp_mode, loop_mode);
    void update();
    void update(int dim);
    void zeroCrossed();
    void burn(unsigned long currentMicros);
  private:
    int _pin;
    volatile boolean _zeroCrossed;
    int _dim;
    int _dimCount;
    unsigned long _previousMicros;
    boolean _isBurning;
};

#endif
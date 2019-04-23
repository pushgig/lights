/*
  PowerSSR.h
*/
#ifndef PowerSSR_h
#define PowerSSR_h

// 60hz AC mains
#define AC_FREQUENCY 60
#define SSR_COUNT 5
#define MAX_BRIGHT 10
#define MIN_BRIGHT 127

#define MAX_DIM 127
#define MIN_DIM 10

#include <TweenDuino.h>

class PowerSSR
{
  public:
    PowerSSR();
    void init(int pin);
    void update(int dim);
    void zeroCrossed();
    void burn(unsigned long currentMicros);
    void wipe();
    TweenDuino::Timeline timeline;
    float value = MAX_DIM;
  private:
    byte _pin;
    volatile boolean _zeroCrossed;
    byte _dim;
    byte _dimCount;
    unsigned long _previousMicros;
    boolean _isBurning;
};

#endif
/*
  PowerSSR.h
*/
#ifndef PowerSSR_h
#define PowerSSR_h

// 60hz AC mains
#define AC_FREQUENCY 60
#define SSR_COUNT 5

#define LIGHT_OFF 0
#define LIGHT_MIN 8
#define LIGHT_MED 30
#define LIGHT_MAX 60

#include <TweenDuino.h>

class PowerSSR
{
  public:
    PowerSSR();
    void init(int pin);
    void update(int brightness);
    void zeroCrossed();
    void burn(unsigned long currentMicros);
    void wipe();
    TweenDuino::Timeline timeline;
    float value = LIGHT_MIN;
  private:
    byte _pin;
    volatile boolean _zeroCrossed;
    byte _dim;
    byte _dimCount;
    unsigned long _previousMicros;
    boolean _isBurning;
};

#endif
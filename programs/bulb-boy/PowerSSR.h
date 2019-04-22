/*
  PowerSSR.h
*/
#ifndef PowerSSR_h
#define PowerSSR_h

#define SSR_COUNT 5
#define MAX_BRIGHT 10
#define MIN_BRIGHT 127

#define MAX_DIM 127
#define MIN_DIM 10

class PowerSSR
{
  public:
    PowerSSR();
    void init(int pin);
    void update(int dim);
    void zeroCrossed();
    void burn(unsigned long currentMicros);
  private:
    byte _pin;
    volatile boolean _zeroCrossed;
    byte _dim;
    byte _dimCount;
    unsigned long _previousMicros;
    boolean _isBurning;
};

#endif
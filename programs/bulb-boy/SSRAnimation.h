/*
  SSRAnimation.h
*/
#ifndef SSRAnimation_h
#define SSRAnimation_h

#include "Arduino.h"
#include "PowerSSR.h"

class SSRAnimation
{
  public:
    SSRAnimation(PowerSSR* ssrs) { 
      _ssrs = ssrs;
    }
    
    void intensity(byte value) {
      _intensity = value;
    }

    void speed(byte value) {
      _speed = value;
    }
    
    void destroy() {
      for (byte i = 0; i < SSR_COUNT; i++) {
        _ssrs[i].timeline.wipe();
      }
    }
    
    boolean canBump = 0;
    virtual void start(uint32_t millis) = 0;
    virtual void update(uint32_t millis) = 0;
    virtual void bump(uint32_t millis) = 0;
    virtual void stop() = 0;
  protected:
    PowerSSR* _ssrs;
    byte _speed = 127;
    byte _intensity = 127;
};

#endif
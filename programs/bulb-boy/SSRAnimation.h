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
      Serial.print("Intensity: ");
      Serial.println(value);
      _intensity = value;
    }

    void speed(byte value) {
      Serial.print("Speed: ");
      Serial.println(value);
      _speed = value;
    }
    
    virtual ~SSRAnimation(){}
    virtual void start(uint32_t millis) = 0;
    // virtual void intensity(byte value) = 0;
    // virtual void speed(byte value) = 0;
    virtual void update(uint32_t millis) = 0;
    virtual void stop() = 0;
  protected:
    PowerSSR* _ssrs;
    byte _speed = 127;
    byte _intensity = 127;
};

#endif
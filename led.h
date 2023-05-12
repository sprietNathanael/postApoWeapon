#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#define PIN 0
#define BRIGHTNESS 255
class Led
{
  public:
    Led();
    void setup();
    void loop();
    void setPulse();
    void setLoading();
    void setUnloading();
    void setRocketFire();
    void clearFlags();
    void loading(unsigned long delay);
    void unloading(unsigned long delay);
    void fire(unsigned long delay);
    void rocketFire(unsigned long delay);
    void colorWipeCircle(uint32_t c, int currentCircle);
  private:
    const int circles[5] = {24,16,12, 8, 1};
    const Adafruit_NeoPixel strip = Adafruit_NeoPixel(61, PIN, NEO_GRB + NEO_KHZ800);
    int loading_flag;
    int unloading_flag;
    int fire_flag;
    int rocketFire_flag;
    uint32_t generalColor;
};
// the #include statment and code go here...

#endif

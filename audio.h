#ifndef AUDIO_H
#define AUDIO_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define SOUND_ROCKET 2
#define SOUND_PULSE 1
#define SOUND_LOADING 4
#define SOUND_UNLOADING 3

class Audio
{
  public:
    Audio();
    void setup();
    void playPulse();
    void playLoading();
    void playUnloading();
    void playRocket();
  private:
    const int circles[5] = {24,16,12, 8, 1};
    //const SoftwareSerial mySoftwareSerial = SoftwareSerial(10, 11);
    const DFRobotDFPlayerMini myDFPlayer;
};
// the #include statment and code go here...

#endif

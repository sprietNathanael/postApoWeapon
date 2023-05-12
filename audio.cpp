#include "Arduino.h"
#include "audio.h"

Audio::Audio()
{ 
}

void Audio::setup() {
  SoftwareSerial mySoftwareSerial(10, 11);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void Audio::playPulse()
{
  myDFPlayer.loop(SOUND_PULSE);
}
void Audio::playLoading()
{
  myDFPlayer.play(SOUND_LOADING);
}

void Audio::playUnloading()
{
  myDFPlayer.play(SOUND_UNLOADING);
}

void Audio::playRocket()
{
  myDFPlayer.play(SOUND_ROCKET);
}


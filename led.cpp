#include "Arduino.h"
#include "led.h"

Led::Led()
{ 
  loading_flag = 0;
  unloading_flag = 0;
  fire_flag = 0;
  rocketFire_flag = 0;  
  generalColor = 0;
}

void Led::setup() {
  
  //Serial.begin(115200);
  generalColor = strip.Color(0, 0, 1*BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
}

void Led::loop() {
  
  /*Serial.print("loading : ");
  Serial.print(loading_flag);
  Serial.print(" unloading : ");
  Serial.print(unloading_flag);
  Serial.print(" fire : ");
  Serial.print(fire_flag);
  Serial.print(" rocket : ");
  Serial.print(rocketFire_flag);
  Serial.print("\n");*/
  
  if(loading_flag == 1)
  {
    loading(30);
  }
  if(unloading_flag == 1)
  {
    unloading(100);
  }
  if(fire_flag == 1)
  {
    fire(70);
  }
  if(rocketFire_flag == 1)
  {
    rocketFire(50);
  }
  //colorWipeCircle(strip.Color(255, 0, 0), 4);
}

void Led::clearFlags()
{
  loading_flag = 0;
  unloading_flag = 0;
  rocketFire_flag = 0;
  fire_flag = 0;
}

void Led::setPulse()
{
  clearFlags();
  fire_flag = 1;
}

void Led::setLoading()
{
  clearFlags();
  loading_flag = 1;
}

void Led::setUnloading()
{
  clearFlags();
  unloading_flag = 1;
}


void Led::setRocketFire()
{
  clearFlags();
  rocketFire_flag = 1;
}


void Led::loading(unsigned long delay)
{
  static unsigned long timer = 0;
  static int currentCircle = 4;
  if(timer == 0)
  {
    timer = millis();  
  }
  else if(millis() - timer >= delay)
  {
    timer = millis();
    if(currentCircle >= 0)
    {
      colorWipeCircle(generalColor, currentCircle);
      currentCircle--;
    }
    else
    {
      loading_flag = 0;
      timer = 0;
      currentCircle = 4;
    }
 
  }
}

void Led::unloading(unsigned long delay)
{
  static unsigned long timer = 0;
  static int currentCircle = 0;
  if(timer == 0)
  {
    timer = millis();  
  }
  else if(millis() - timer >= delay)
  {
    timer = millis();
    if(currentCircle < 5)
    {
      colorWipeCircle(strip.Color(0, 0, 0), currentCircle);
      currentCircle++;
    }
    else
    {
      unloading_flag = 0;
      timer = 0;
      currentCircle = 0;
    }
 
  }
}

void Led::fire(unsigned long delay)
{
  static unsigned long timer = 0;
  static int currentCircle = 4;
  if(timer == 0)
  {
    timer = millis();  
  }
  else if(millis() - timer >= delay)
  {
    timer = millis();
    if(currentCircle >= 0)
    {
      colorWipeCircle(strip.Color(0, 0, 0), currentCircle);
      
      if(currentCircle < 4)
      {
        colorWipeCircle(generalColor, currentCircle+1);
      }
      else
      {
        colorWipeCircle(generalColor, 0);
      }
      currentCircle--;
      
    }
    else
    {
      timer = 0;
      currentCircle = 4;
    }
 
  }
}

void Led::rocketFire(unsigned long delay)
{
  static unsigned long timer = 0;
  static int currentCircle = 4;
  static int first = 1;
  static uint32_t currentColor = generalColor;
  if(timer == 0)
  {
    timer = millis();  
  }
  else if(millis() - timer >= delay)
  {
    timer = millis();
    if(currentCircle >= 0)
    {
      colorWipeCircle(currentColor, currentCircle);
      currentCircle--;
    }
    else if(first)
    {
      currentColor = strip.Color(0, 0, 0);
      currentCircle = 4;
      first = 0;
    }
    else
    {
      rocketFire_flag = 0;
      timer = 0;
      currentCircle = 4;
      first = 1;
      currentColor = generalColor;
    }
 
  }
}

void Led::colorWipeCircle(uint32_t c, int currentCircle)
{
  int start = 0;
  for(int i = 1; i <= currentCircle; i++)
  {
    start += circles[i-1];
  }
  for(int i = start; i < start+circles[currentCircle]; i++)
  {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


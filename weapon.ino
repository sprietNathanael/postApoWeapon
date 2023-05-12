#include "lcd.h"
#include "led.h"
#include "audio.h"

#define BUTTON_MODE_IN 7
#define BUTTON_MODE_VCC 6
#define BUTTON_FIRE_IN 9
#define BUTTON_FIRE_VCC 8
#define PULSE_MODE 0
#define ROCKET_MODE 1
#define FIRE_PRESSED 0

#define LOADING_DELAY 50
#define UNLOADING_DELAY 400
#define ROCKET_DELAY 800

Lcd lcd;
Led led;
Audio audio;
int currentMode;

int loading_flag = 0;
int unloading_flag = 0;
int pulse_flag = 0;
int rocket_flag = 0;

void setup() {
  
  //Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(BUTTON_MODE_IN, INPUT_PULLUP);
  pinMode(BUTTON_FIRE_IN, INPUT_PULLUP);
  pinMode(BUTTON_MODE_VCC, OUTPUT);
  pinMode(BUTTON_FIRE_VCC, OUTPUT);

  digitalWrite(BUTTON_MODE_VCC,LOW);
  digitalWrite(BUTTON_FIRE_VCC,LOW);
  lcd.setup();
  led.setup();
  audio.setup();
  /*firePulse();
  delay(2000);
  audio.playUnloading();*/

}

void loop() {

  //------------------- Mode buttons test ------------------------------
  if(digitalRead(BUTTON_MODE_IN) == PULSE_MODE)
  {
    lcd.displayMode1();
    currentMode = PULSE_MODE;
  }
  else if(digitalRead(BUTTON_MODE_IN) == ROCKET_MODE)
  {
    lcd.displayMode2();
    currentMode = ROCKET_MODE;
  }
  /*Serial.print(currentMode);
  Serial.print(" - ");
  Serial.print(digitalRead(BUTTON_MODE_IN));
  Serial.print(" - ");
  Serial.print(digitalRead(BUTTON_MODE_IN) == ROCKET_MODE);
  Serial.print("\n");*/

  //----------------------- fire buton test ------------------------------

  // If the fire button is pressed
  if(digitalRead(BUTTON_FIRE_IN) == FIRE_PRESSED)
  {
    
    // If we are in rocket mode and the rocket flag is not rised
    if(currentMode == ROCKET_MODE && rocket_flag == 0)
    {
      rocket_flag = 1;
    }
    // if we are in pulse mode
    else if(currentMode == PULSE_MODE)
    {
      // if the fire is not loaded
      if(loading_flag == 0)
      {
        // raise the loading flag
        loading_flag = 1;
      }
      // if the fire is loaded but not pulsing
      else if(loading_flag == 2 && pulse_flag == 0)
      {
        firePulse();
      }
    }
  }
  // If the fire button is not pressed but fire is pulsing
  else if(currentMode == PULSE_MODE && pulse_flag == 1)
  {
    // drop the rocket flag
    rocket_flag = 0;
    // drop the loading and pulsing flags
    pulse_flag = 0;
    loading_flag = 0;
    // rise the unloading flag
    unloading_flag = 1;
  }
  // If the fire button is not pressed and the rocket timeout is expired
  else if(currentMode == ROCKET_MODE && rocket_flag == 2)
  {
    rocket_flag = 0;
  }

  //----------------- flag testing------------------- 
  if(loading_flag == 1)
  {
    loadPulse(LOADING_DELAY);
  }
  
  if(unloading_flag == 1)
  {
    unloadPulse(UNLOADING_DELAY);
  }

  if(rocket_flag == 1)
  {
    rocketFire(ROCKET_DELAY);
  }

  //------------------- looping call ------------------------
  
  //lcd.loop();
  led.loop();

}

void firePulse()
{
  // rise the firing flag
  pulse_flag = 1;
  audio.playPulse();
  led.setPulse();
}

void loadPulse(unsigned long delay)
{
  static unsigned long timer = 0;
  // If timer has not yet begun  
  if(timer == 0)
  {
    lcd.loadingDisplay();
    audio.playLoading();
    led.setLoading();
    timer = millis();  
  }
  // else if time has reach the end
  else if(millis() - timer >= delay)
  { 
    timer = 0;
    // set the flag to loaded
    loading_flag = 2;
  }
}

void unloadPulse(unsigned long delay)
{
  static unsigned long timer = 0;
  // If timer has not yet begun
  if(timer == 0)
  {
    lcd.unloadingDisplay();
    audio.playUnloading();
    led.setUnloading();
    timer = millis();  
  }
  // else if time has reach the end
  else if(millis() - timer >= delay)
  { 
    timer = 0;
    unloading_flag = 0;
  }
}

void rocketFire(unsigned long delay)
{
  static unsigned long timer = 0;
  // If timer has not yet begun  
  if(timer == 0)
  {
    led.setRocketFire();
    audio.playRocket(); 
    timer = millis();  
  }
  // else if time has reach the end
  else if(millis() - timer >= delay)
  { 
    timer = 0;
    // set the flag to loaded
    rocket_flag = 2;
  }
}


#include "Arduino.h"
#include "lcd.h"

Lcd::Lcd()
{ 
  display_blocks_flag = 0;
  hide_blocks_flag = 0;
  currentMode = -1;
}

void Lcd::setup() {
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, contrast);
  lcd.createChar(0, fullBlock);
  lcd.createChar(1, emptyBlock);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  bootDisplay();
}

void Lcd::loop() {
  if(display_blocks_flag)
  {
    displayBlocksBar(100);
  }
  if(hide_blocks_flag)
  {
    hideBlocksBar(100);
  }
}

void Lcd::bootDisplay()
{
  lcd.setCursor(0,0);
  lcd.print("Destructor v1.5");
  loadingDisplay();
}

void Lcd::loadingDisplay()
{
  display_blocks_flag = 1;
}

void Lcd::unloadingDisplay()
{
  hide_blocks_flag = 1;
}

void Lcd::displayBlocksBar(unsigned long delay)
{
  static unsigned long timer = 0;
  static int cursorPos = 0;
  if(timer == 0)
  {
    timer = millis();  
  }
  else if(millis() - timer >= delay)
  {
    timer = millis();
    if(cursorPos < 16)
    {
      lcd.setCursor(cursorPos,1);
      lcd.write(byte(0));
      cursorPos ++;
    }
    else
    {
      display_blocks_flag = 0;
    }
 
  }  
}


void Lcd::hideBlocksBar(unsigned long delay)
{
  static unsigned long timer = 0;
  static int cursorPos = 15;
  if(timer == 0)
  {
    timer = millis();  
  }
  else if(millis() - timer >= delay)
  {
    timer = millis();
    if(cursorPos < 16)
    {
      lcd.setCursor(cursorPos,1);
      lcd.write(byte(1));
      cursorPos --;
    }
    else
    {
      hide_blocks_flag = 0;         
      lcd.setCursor(0,1);
      lcd.print("Ready to fire");
    }
 
  }  
}

void Lcd::displayMode1()
{
  if(currentMode != PULSE_MODE)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mode 1");
    lcd.setCursor(0,1);
    lcd.print("Ready to fire");  
    currentMode = PULSE_MODE;
  }
  
}

void Lcd::displayMode2()
{
  if(currentMode != ROCKET_MODE)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mode 2");
    lcd.setCursor(0,1);
    lcd.print("Ready to fire");
    currentMode = ROCKET_MODE;
  }
}

#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
#include <LiquidCrystal.h>

#define PULSE_MODE 1
#define ROCKET_MODE 0

class Lcd
{
  public:
    Lcd();
    void setup();
    void loop();
    void bootDisplay();
    void loadingDisplay();
    void unloadingDisplay();
    void displayBlocksBar(unsigned long delay);
    void hideBlocksBar(unsigned long delay);
    void displayMode1();
    void displayMode2();
  private:
    const int rs = 13, en = 12, d4 = 4, d5 = 3, d6 = 2, d7 = 1;
    const int contrastPin = 5;
    const int contrast = 130;
    const LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);
    const byte fullBlock[8] = {
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
    };
    const byte emptyBlock[8] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };
    int display_blocks_flag;
    int hide_blocks_flag;
    int currentMode;
};
// the #include statment and code go here...

#endif

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("JNU Arduino!");
  delay(5000);
}


void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("world!");
  lcd.setCursor(0, 1);
  lcd.print("Arduino!");
  delay(5000);
}

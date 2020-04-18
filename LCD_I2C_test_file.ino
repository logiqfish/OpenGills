#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

/*declaring variables*/
int t = 0;

void setup()
{
  lcd.begin();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  delay(2000);
  lcd.clear();
}


void loop()
{
  t = millis() / 1000;
  lcd.setCursor(1, 0);
  lcd.print("Time since On:");
  lcd.setCursor(7,0);
  lcd.print(t);
  delay(1000);
  lcd.clear();

}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
// Set the LCD I2C address, if it's not working try 0x27 or 0x3F.

byte airport[] = 
{
  B00000,
  B00001,
  B11110,
  B00110,
  B11010,
  B01010,
  B00000,
  B11111
};

void setup()
{
  
  lcd.createChar(7, airport);

}

void loop() 
{
  lcd.setCursor(0, 1);
  lcd.write(7);
}

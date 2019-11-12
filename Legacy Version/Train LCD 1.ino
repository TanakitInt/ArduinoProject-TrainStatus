//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27 or 0x3F.

void setup()
{
  lcd.begin(16, 2);  // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   //backlight on
}

void loop()
{
  lcd.setCursor(0, 0); //First line
  
  lcd.display();  
  lcd.print("This Door Open");
  delay(2000);

  lcd.noDisplay();
  delay(500);
  lcd.clear();
  
  lcd.display();
  //このドアが開きます
  //コノドアガヒラキマス
  
  lcd.print(char(186));
  lcd.print(char(201));
  lcd.print(char(196));
  lcd.print(char(222));
  lcd.print(char(177));
  lcd.print(char(182));
  lcd.print(char(222));
  lcd.print(char(203));
  lcd.print(char(215));
  lcd.print(char(183));
  lcd.print(char(207));
  lcd.print(char(189));
  delay(2000);

  lcd.noDisplay();
  delay(500);

  lcd.display();
  lcd.clear();

  
  for (int positionCounter = 0; positionCounter < 82; positionCounter++)
  {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    lcd.setCursor(0, 1); //Second line
    lcd.print(" Watch your step when leaving the train. ");
    // wait a bit:
    delay(150);
  }
  
  lcd.clear();

}
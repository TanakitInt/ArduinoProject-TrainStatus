//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
// Set the LCD I2C address, if it's not working try 0x27 or 0x3F.

int screenWidth = 16;
int screenHeight = 2;

//Japanese Text
//このドアが開きます
//コノドアガヒラキマス
String ko = String(char(186));
String no = String(char(201));
String to = String(char(196));
String dbline = String(char(222));
String a = String(char(177));
String ka = String(char(182));
//String dbline = String(char(222));
String hi = String(char(203));
String ra = String(char(215));
String ki = String(char(183));
String ma = String(char(207));
String su = String(char(189));

String jp_text = ko + no + to + dbline + a + ka + dbline + hi + ra + ki + ma + su;

//airport icon
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

// line1 = static
String line1 = "This Door Open";
String line1_1 = jp_text;
// line2 = scroll
String line2 = " This train is bound for DonMuang Int.Airport. ";

int stringStart = 0;
int stringStop = 0;

int scrollCursor = screenWidth;

void setup() 
{
  lcd.begin(screenWidth,screenHeight);
  lcd.backlight();   //backlight on

  lcd.createChar(1, airport); //create custom character
}

void loop() 
{
  lcd.setCursor(0, 0);
  lcd.print(line1);
  //lcd.print(line1_1);
  lcd.setCursor(0, 1);

  lcd.write(1);
  lcd.print(line2.substring(stringStart,stringStop));

  delay(150);
  lcd.clear();

  if(stringStart == 0 && scrollCursor > 0)
  {
    scrollCursor--;
    stringStop++;
  }

  else if (stringStart == stringStop)
  {
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  }

  else if (stringStop == line2.length() && scrollCursor == 0) 
  {
    stringStart++;
  }

  else 
  {
    stringStart++;
    stringStop++;
  }
}
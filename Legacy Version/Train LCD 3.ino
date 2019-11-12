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

// screen1_line1 = static
String screen1_line1 = "This Door Open";
// screen1_line2 = scroll
String screen1_line2 = " This is EXPRESS train bound for DonMuang Int.Airport. Next station : Laksi ";

String screen2_line1 = "APPORACHING";
String screen2_line2 = " Please mind your step when leaving the train. ";

int stringStart_1 = 0;
int stringStop_1 = 0;

int scrollCursor_1 = screenWidth;

int stringStart_2 = 0;
int stringStop_2 = 0;

int scrollCursor_2 = screenWidth;

void setup() 
{
  lcd.begin(screenWidth,screenHeight);
  lcd.backlight();   //backlight on

  lcd.createChar(1, airport); //create custom character
}

void loop() 
{
  while(true)
  {
    for (int loop_counter_1 = 0; loop_counter_1 < 100; loop_counter_1++)
    {
      lcd.clear();
      screen1();
      
    }
  
    for (int loop_counter_2 = 0; loop_counter_2 < 100; loop_counter_2++)
    {
      lcd.clear();
      screen2();
    }    
  }
}


void screen1()
{
  lcd.setCursor(0, 0);
  lcd.print(screen1_line1);
  lcd.setCursor(0, 1);

  lcd.write(1);
  lcd.print(screen1_line2.substring(stringStart_1,stringStop_1));

  if(stringStart_1 == 0 && scrollCursor_1 > 0)
  {
    scrollCursor_1--;
    stringStop_1++;
  }

  else if (stringStart_1 == stringStop_1)
  {
    stringStart_1 = stringStop_1 = 0;
    scrollCursor_1 = screenWidth;
  }

  else if (stringStop_1 == screen1_line2.length() && scrollCursor_1 == 0) 
  {
    stringStart_1++;
  }

  else 
  {
    stringStart_1++;
    stringStop_1++;
  }

  delay(125);
}

void screen2()
{
  lcd.setCursor(0, 0);
  lcd.print(screen2_line1);
  lcd.setCursor(0, 1);

  lcd.print(screen2_line2.substring(stringStart_2,stringStop_2));

  if(stringStart_2 == 0 && scrollCursor_2 > 0)
  {
    scrollCursor_2--;
    stringStop_2++;
  }

  else if (stringStart_2 == stringStop_2)
  {
    stringStart_2 = stringStop_2 = 0;
    scrollCursor_2 = screenWidth;
  }

  else if (stringStop_2 == screen2_line2.length() && scrollCursor_2 == 0) 
  {
    stringStart_2++;
  }

  else 
  {
    stringStart_2++;
    stringStop_2++;
  }

  delay(125);
}


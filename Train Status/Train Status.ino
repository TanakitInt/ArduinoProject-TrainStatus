//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
// Set the LCD I2C address, if it's not working try 0x27 or 0x3F.

int screenWidth = 16;
int screenHeight = 2;

//Temperature sensor
//set analog pin
int ThermistorPin = A0;

//set constant resistance for know resistor
float R1 = 10000;

//initial value for Steinhart-Hart equation
//used for convert the resistance of the thermistor to a temperature reading
int Vo;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//PHOTO RESISTOR
int sensorPin = A7;   // select the analog input pin for the photoresistor
int threshold = 400;  // analog input trigger level from photoresistor
int sensorValue = 0;  // photoresistor value read from analog input pin
int ledPin = 52;

//Japanese Text

//このドアが開きます
//コノドアガヒラキマス
String katakana_ko = String(char(186));
String katakana_no = String(char(201));
String katakana_to = String(char(196));
String katakana_dbline = String(char(222));
String katakana_a = String(char(177));
String katakana_ka = String(char(182));
String katakana_hi = String(char(203));
String katakana_ra = String(char(215));
String katakana_ki = String(char(183));
String katakana_ma = String(char(207));
String katakana_su = String(char(189));

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

//Hiragana character set
//あ
byte hiragana_a[] = 
{
  B00100,
  B11111,
  B00100,
  B00101,
  B01010,
  B10101,
  B10101,
  B01001
};

//い
byte hiragana_i[] = 
{
  B10000,
  B10010,
  B10001,
  B10001,
  B10000,
  B10000,
  B01000,
  B00110
};

//う
byte hiragana_u[] = 
{
  B11110,
  B00001,
  B11110,
  B00001,
  B00001,
  B00001,
  B00010,
  B00110
};

//え
byte hiragana_e[] = 
{
  B11110,
  B00001,
  B11110,
  B00001,
  B00110,
  B01000,
  B11100,
  B10111
};

//お
byte hiragana_o[] = 
{
  B00101,
  B00100,
  B11111,
  B00100,
  B01110,
  B10101,
  B10101,
  B01001
};

//か
byte hiragana_ka[] = 
{
  B01001,
  B01001,
  B11110,
  B01001,
  B01001,
  B01001,
  B01001,
  B10010
};

//き
byte hiragana_ki[] = 
{
  B00100,
  B11111,
  B00100,
  B11111,
  B00100,
  B11100,
  B10001,
  B01110
};

//く
byte hiragana_ku[] = 
{
  B00010,
  B00100,
  B01000,
  B10000,
  B01000,
  B00100,
  B00010,
  B00001
};

//け
byte hiragana_ke[] = 
{
  B10010,
  B10010,
  B10111,
  B10010,
  B10010,
  B10010,
  B10010,
  B01010
};

//こ
byte hiragana_ko[] = 
{
  B11111,
  B00001,
  B00010,
  B00000,
  B00000,
  B01000,
  B10000,
  B11111
};

//さ
byte hiragana_sa[] = 
{
  B00100,
  B11111,
  B00100,
  B00100,
  B01100,
  B10000,
  B10001,
  B11110
};

//し
byte hiragana_shi[] = 
{
  B10000,
  B10000,
  B10000,
  B10000,
  B10001,
  B10001,
  B10001,
  B01110
};

//す
byte hiragana_su[] = 
{
  B00100,
  B11111,
  B00100,
  B11100,
  B10100,
  B11100,
  B00100,
  B01100
};

//せ
byte hiragana_se[] = 
{
  B01010,
  B01010,
  B11111,
  B01010,
  B01010,
  B01010,
  B01000,
  B01111
};

//そ
byte hiragana_so[] = 
{
  B11111,
  B00100,
  B01000,
  B11111,
  B00010,
  B00100,
  B01000,
  B01111
};

//た
byte hiragana_ta[] = 
{
  B10000,
  B11100,
  B10000,
  B10111,
  B10001,
  B10000,
  B10100,
  B10111
};

//ち
byte hiragana_chi[] = 
{
  B00100,
  B11111,
  B00100,
  B00100,
  B00111,
  B00001,
  B10001,
  B01110
};

//つ
byte hiragana_tsu[] = 
{
  B00000,
  B00000,
  B11110,
  B00001,
  B00001,
  B00001,
  B00010,
  B11100
};


//て
byte hiragana_te[] = 
{
  B11111,
  B00010,
  B00100,
  B01000,
  B10000,
  B10000,
  B01000,
  B00110
};

//と
byte hiragana_to[] = 
{
  B01000,
  B01001,
  B01110,
  B01000,
  B10000,
  B10000,
  B01000,
  B00111
};

//な
byte hiragana_na[] = 
{
  B10000,
  B11100,
  B10000,
  B10011,
  B10000,
  B10010,
  B10011,
  B10110
};

//に
byte hiragana_ni[] = 
{
  B10000,
  B10111,
  B10001,
  B10000,
  B10000,
  B10000,
  B10100,
  B10111
};

//ぬ
byte hiragana_nu[] = 
{
  B00010,
  B10010,
  B01110,
  B11011,
  B10101,
  B10101,
  B11011,
  B10011
};

//ね
byte hiragana_ne[] = 
{
  B01000,
  B11011,
  B01101,
  B01001,
  B11001,
  B01011,
  B10101,
  B10011
};

//の
byte hiragana_no[] = 
{
  B00000,
  B01110,
  B10101,
  B10101,
  B10101,
  B10101,
  B10101,
  B01101
};

//は
byte hiragana_ha[] = 
{
  B10010,
  B10111,
  B10010,
  B10010,
  B10010,
  B10010,
  B10111,
  B10110
};

//ひ
byte hiragana_hi[] = 
{
  B00000,
  B11011,
  B01010,
  B01001,
  B01001,
  B01001,
  B01010,
  B01110
};

//ふ
byte hiragana_hu[] = 
{
  B11111,
  B00010,
  B00100,
  B10101,
  B10101,
  B00010,
  B00010,
  B00100
};

//へ
byte hiragana_he[] = 
{
  B00000,
  B00000,
  B01000,
  B10100,
  B00010,
  B00001,
  B00000,
  B00000
};

//ほ
byte hiragana_ho[] = 
{
  B10010,
  B10111,
  B10010,
  B10111,
  B10010,
  B10111,
  B11010,
  B10100
};

//ま
byte hiragana_ma[] = 
{
  B00100,
  B11111,
  B00100,
  B11111,
  B00100,
  B01110,
  B10101,
  B01100
};

//み
byte hiragana_mi[] = 
{
  B11100,
  B00101,
  B00101,
  B00101,
  B01111,
  B10101,
  B10101,
  B11001
};

//む
byte hiragana_mu[] = 
{
  B00101,
  B00100,
  B11111,
  B00100,
  B11100,
  B10100,
  B11101,
  B00111
};

//め
byte hiragana_me[] = 
{
  B00000,
  B10001,
  B01010,
  B01111,
  B11101,
  B10101,
  B11001,
  B10001
};

//も
byte hiragana_mo[] = 
{
  B01000,
  B11100,
  B01000,
  B11100,
  B01000,
  B01001,
  B01010,
  B00100
};

//や
byte hiragana_ya[] = 
{
  B01010,
  B11111,
  B01001,
  B01010,
  B01000,
  B01000,
  B01000,
  B00100
};

//ゆ
byte hiragana_yu[] = 
{
  B00000,
  B10100,
  B10110,
  B11101,
  B10101,
  B00101,
  B01110,
  B00100
};

//よ
byte hiragana_yo[] = 
{
  B00100,
  B00100,
  B00111,
  B00100,
  B00100,
  B01111,
  B10100,
  B01100
};

//ら
byte hiragana_ra[] = 
{
  B11111,
  B00000,
  B10000,
  B10000,
  B11110,
  B00001,
  B00010,
  B11100
};

//り
byte hiragana_ri[] = 
{
  B00010,
  B10101,
  B11001,
  B10001,
  B00001,
  B00001,
  B00010,
  B00100
};

//る
byte hiragana_ru[] = 
{
  B11111,
  B00010,
  B00100,
  B01100,
  B10010,
  B00101,
  B01011,
  B01110
};

//れ
byte hiragana_re[] = 
{
  B01000,
  B11111,
  B01001,
  B01001,
  B01001,
  B01010,
  B01010,
  B01011
};

//ろ
byte hiragana_ro[] = 
{
  B11111,
  B00010,
  B00100,
  B01100,
  B10010,
  B00001,
  B00001,
  B01110
};

//わ
byte hiragana_wa[] = 
{
  B01000,
  B11111,
  B01001,
  B01001,
  B01001,
  B01010,
  B01010,
  B01011
};

//を
byte hiragana_wo[] = 
{
  B01000,
  B11110,
  B01000,
  B01111,
  B11000,
  B10100,
  B10001,
  B01110
};

//ん
byte hiragana_n[] = 
{
  B10000,
  B10000,
  B10000,
  B10000,
  B10100,
  B11010,
  B10011,
  B10010
};

//。
byte hiragana_fullStop[] = 
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00010,
  B00101,
  B00010
};

//upper circle
byte hiragana_upperCircle[] = 
{
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

//upper double line
byte hiragana_upperDBLine[] = 
{
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

//~
byte hiragana_tilde[] = 
{
  B00000,
  B00000,
  B00000,
  B01010,
  B10100,
  B00000,
  B00000,
  B00000
};


//String jp_text = ko + no + to + dbline + a + ka + dbline + hi + ra + ki + ma + su;

//screen 1
String screen1_next = "Next:";
String screen1_line1 = " DonMuang Int.Airport ";
String screen1_line2 = " This is EXPRESS train bound for DonMuang Int.Airport. ";

//screen 2
String screen2_line1 = "APPORACHING";
String screen2_line2 = " Please mind your step when leaving the train. ";

//screen 3
String screen3_line1 = "This door open";
String screen3_line2 = ""; //Japanese Text

//screen 1 line 1
int stringStart_0 = 0;
int stringStop_0 = 0;

int scrollCursor_0 = (screenWidth - screen1_next.length());

//screen 1 line 2
int stringStart_1 = 0;
int stringStop_1 = 0;

int scrollCursor_1 = screenWidth;

//screen 2
int stringStart_2 = 0;
int stringStop_2 = 0;

int scrollCursor_2 = screenWidth;

//screen 3
int stringStart_3 = 0;
int stringStop_3 = 0;

int scrollCursor_3 = screenWidth;

//screen 4

//screen 4 has no scroll text

void setup() 
{
  lcd.begin(screenWidth,screenHeight);
  lcd.backlight();   //backlight on

  //Temperature sensor
  Serial.begin(9600);

  //PHOTO RESISTOR
  pinMode(ledPin, OUTPUT);

  //Custom character set

  //airport icon
  lcd.createChar(1, airport);

  //hiragana character set

  //Maximum 7 (0-7) can be used. Otherwise It will be sensored.

  //このドアが開きます

  //lcd.createChar(#, hiragana_a);
  //lcd.createChar(#, hiragana_i);
  //lcd.createChar(#, hiragana_u);
  //lcd.createChar(#, hiragana_e);
  //lcd.createChar(#, hiragana_o);
  lcd.createChar(2, hiragana_ka);
  //lcd.createChar(3, hiragana_ki);
  //lcd.createChar(#, hiragana_ku);
  //lcd.createChar(#, hiragana_ke);
  lcd.createChar(4, hiragana_ko);
  //lcd.createChar(#, hiragana_sa);
  //lcd.createChar(#, hiragana_shi);
  lcd.createChar(5, hiragana_su);
  //lcd.createChar(#, hiragana_se);
  //lcd.createChar(#, hiragana_so);
  //lcd.createChar(#, hiragana_ta);
  //lcd.createChar(#, hiragana_chi);
  //lcd.createChar(#, hiragana_tsu);
  //lcd.createChar(#, hiragana_te);
  //lcd.createChar(#, hiragana_to);
  //lcd.createChar(#, hiragana_na);
  //lcd.createChar(#, hiragana_ni);
  //lcd.createChar(#, hiragana_nu);
  //lcd.createChar(#, hiragana_ne);
  lcd.createChar(6, hiragana_no);
  //lcd.createChar(#, hiragana_ha);
  //lcd.createChar(#, hiragana_hi);
  //lcd.createChar(#, hiragana_hu);
  //lcd.createChar(#, hiragana_he);
  //lcd.createChar(#, hiragana_ho);
  lcd.createChar(7, hiragana_ma);
  //lcd.createChar(#, hiragana_mi);
  //lcd.createChar(#, hiragana_mu);
  //lcd.createChar(#, hiragana_me);
  //lcd.createChar(#, hiragana_mo);
  //lcd.createChar(#, hiragana_ya);
  //lcd.createChar(#, hiragana_yu);
  //lcd.createChar(#, hiragana_yo);
  //lcd.createChar(#, hiragana_ra);
  //lcd.createChar(#, hiragana_ri);
  //lcd.createChar(#, hiragana_ru);
  //lcd.createChar(#, hiragana_re);
  //lcd.createChar(#, hiragana_ro);
  //lcd.createChar(#, hiragana_wa);
  //lcd.createChar(#, hiragana_wo);
  //lcd.createChar(#, hiragana_n);
  lcd.createChar(3, hiragana_fullStop);
  //lcd.createChar(#, hiragana_upperCircle);
  //lcd.createChar(#, hiragana_upperDBLine);
  //lcd.createChar(#, hiragana_tilde);
}

void loop() 
{
  while(true)
  {
    for (int loop_counter_1 = 0; loop_counter_1 < 150; loop_counter_1++)
    {
      lcd.clear();
      screen1();
    }
  
    for (int loop_counter_2 = 0; loop_counter_2 < 150; loop_counter_2++)
    {
      lcd.clear();
      screen2();
    } 

    for (int loop_counter_3 = 0; loop_counter_3 < 10; loop_counter_3++)
    {
      lcd.clear();
      screen3();
    }

    for (int loop_counter_4 = 0; loop_counter_4 < 10; loop_counter_4++)
    {
      lcd.clear();
      screen4();
    }
  }
}


void screen1()
{
  {
    //line 1
    lcd.setCursor(0, 0);
    lcd.print(screen1_next);
    lcd.print(screen1_line1.substring(stringStart_0,stringStop_0));

    if(stringStart_0 == 0 && scrollCursor_0 > 0)
    {
      scrollCursor_0--;
      stringStop_0++;
    }

    else if (screen1_line1.length() <= (screenWidth - screen1_next.length()))
    {
      //do nothing
    }

    else if (stringStart_0 == stringStop_0)
    {
      stringStart_0 = stringStop_0 = 0;
      scrollCursor_0 = (screenWidth - screen1_next.length());
    }

    else if (stringStop_0 == screen1_line1.length() && scrollCursor_0 == 0) 
    {
      stringStart_0++;
    }

    else 
    {
      stringStart_0++;
      stringStop_0++;
    }
  }

  //line 2
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

void screen3()
{
  lcd.noBlink();
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print(screen3_line1);

  lcd.setCursor(0, 1);
  lcd.write(4); //こ
  lcd.write(6); //の
  lcd.print(katakana_to); //ト
  lcd.print(katakana_dbline); //dbline
  lcd.print(katakana_a); //ア
  lcd.write(2); //カ
  lcd.print(katakana_dbline); //dbline
  lcd.print(katakana_hi); //ヒ
  lcd.print(katakana_ra); //ラ
  lcd.print(katakana_ki); //キ
  lcd.write(7); //ま
  lcd.write(5); //す
  lcd.write(3); //。

//  if(stringStart_3 == 0 && scrollCursor_3 > 0)
//  {
//    scrollCursor_3--;
//    stringStop_3++;
//  }
//
//  else if (stringStart_3 == stringStop_3)
//  {
//    stringStart_3 = stringStop_3 = 0;
//    scrollCursor_3 = screenWidth;
//  }
//
//  else if (stringStop_3 == screen3_line2.length() && scrollCursor_3 == 0) 
//  {
//    stringStart_3++;
//  }
//
//  else 
//  {
//    stringStart_3++;
//    stringStop_3++;
//  }

  lcd.blink();
  delay(1000);
}

void screen4()
{
  //TEMPERATURE
  //get analogRead from analog pin
  Vo = analogRead(ThermistorPin);

  //Steinhart-Hart equation
  //the T ouput is Kelvin
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  //Convert Kelvin to Celsius
  T = T - 273.15;

  //print the value  
  Serial.print(T);
  Serial.print(",");

  //Setup LCD line

  lcd.setCursor(0, 0); //First line

  //print the temperature value
  lcd.print("Temp  : ");

  lcd.print(T);
  lcd.println(" C  ");

  //PHOTO RESISTOR
  lcd.setCursor(0, 1); //Second line

  Serial.print(analogRead(sensorPin));
  Serial.print(",");
  
  //print a light value
  lcd.print("Light : ");

  lcd.print(analogRead(sensorPin));

  if (analogRead(sensorPin) < threshold)
  {
    digitalWrite(ledPin, HIGH);
    Serial.print("ON!");
    Serial.println(",");
    
    lcd.print(" ON!  ");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    Serial.print("OFF");
    Serial.println(",");
    
    lcd.print(" OFF  ");
  }

  //set delay
  delay(1000);

}
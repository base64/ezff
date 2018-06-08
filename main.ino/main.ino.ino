#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object
volatile boolean ezLCDInt = false;
volatile int ffScreen = 0;
unsigned int tmpTime = 12;
unsigned int tmpTimeMin = 00;

String tmpTimeStr;
String tmpTimeMinStr;
String tmpZero;

void setup()
{
  tmpTimeStr = String(tmpTime);
  tmpTimeMinStr = String(tmpTimeMin);
  tmpZero = String("01");
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls();
  lcd.font("lcd72");
}

void drawHour() {
  lcd.xy(60, 110);
  lcd.color(168);
  lcd.box(75, 75, true);
  lcd.color(BLACK);
  tmpTimeStr = String(tmpTime);
  
  if(tmpTime <= 9) {
    String tmp = "0";
    tmp += tmpTimeStr;
    lcd.printString(tmp.c_str());
  } else {
    lcd.printString(tmpTimeStr.c_str());
  }
  
}

void loop() {
 // green pill bg
  lcd.colorID(168, 0, 255, 0);
  
  switch(ffScreen) {
    case(0):
      lcd.picture(0, 0, "welcome2.gif");
      ffScreen = 1;
      delay(2000);
      break;
    case(1):
      lcd.picture(0, 0, "enter.gif");
      lcd.picture(5, 15, "button1.gif");
      
      drawHour();
      lcd.xy(175, 110);
      lcd.printString(tmpTimeMinStr.c_str());
      ffScreen = 2;
      delay(100);
      break;
     case(2):
      if (lcd.touchS() != 0) {
        int x = lcd.touchX();
        int y = lcd.touchY();

        if(x >= 5 & x <=55 ) {
            if(y >= 15 & y < 65) {
                lcd.picture(5, 15, "button1d.gif");
                tmpTime--;
                if(tmpTime < 1)  {
                  tmpTime = 12;  
                }
             
                drawHour();
                
                delay(5);
              } 
          }
          
          lcd.picture(5, 15, "button1.gif");
      }
      break;
  }
  
  
  
  
  
}


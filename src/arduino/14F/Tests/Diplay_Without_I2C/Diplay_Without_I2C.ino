#include <LiquidCrystal.h> 
int Contrast=100;
 LiquidCrystal lcd(A0, A1, 13, 12, 11, 10);  

 void setup()
 {
    analogWrite(A1,Contrast);
     lcd.begin(16, 2);
  } 
     void loop()
 { 
     lcd.setCursor(0, 0);
     lcd.print("Only Innovative");
 
 }

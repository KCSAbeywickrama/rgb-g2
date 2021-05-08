#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16,2);
  lcd.backlight();

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Test_1");
  delay(4000);
  lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Group");
 lcd.setCursor(0,1);
 lcd.print("02");
 delay(4000);
}

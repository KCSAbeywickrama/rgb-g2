//Include wire library for I2C communication
#include <Wire.h>
//Include NewLiquidCrystal library for keypad
#include <LiquidCrystal_I2C.h>

// Making a LCD object using the defined pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Set display type as 16*2
  lcd.begin(16,2);

  // Start Printing from the first raw first column.
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
}



void loop()
{

}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte numRows = 4;
const byte numCols = 4;

char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {A0,A1,A2,A3};
byte colPins[numCols] = {5,4,3,2};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.home();
}

void loop() {
  char keypressed = myKeypad.getKey();
  if(keypressed != NO_KEY)
  {
    Serial.print(keypressed);
    lcd.print(keypressed);
  }

}

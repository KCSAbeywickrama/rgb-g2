#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 3;

byte rgbLed[] = {9, 10, 11};

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

byte rowPins[ROWS] = {6, 5, 4, 3};
byte colPins[COLS] = {0, 1, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(7, 8, 12, 13, 14, 15);
void setup()
{
  lcd.begin(16, 2);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  byte rgbValues[]={250, 220, 10};
  showRGB(rgbValues);
}

void loop()
{
  char customKey = customKeypad.getKey();
  String key = String(customKey);
  lcd.print(key);
}

void showRGB(byte *rgbValues)
{
  for (byte i; i < 3; i++)
  {
    analogWrite(rgbLed[i], rgbValues[i]);
  }
}

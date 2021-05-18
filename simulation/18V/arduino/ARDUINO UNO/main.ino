#include <Keypad.h>
#include <LiquidCrystal.h>
#define OK '#'
#define MODE '*'

const byte ROWS = 4;
const byte COLS = 3;

byte rgbLed[] = {9, 10, 11};
char rgbChars[] = {'R', 'G', 'B'};

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

byte rowPins[ROWS] = {6, 5, 4, 3};
byte colPins[COLS] = {0, 1, 2};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(7, 8, 12, 13, 14, 15);
void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
}

void loop()
{
  showRGB();
}

void writeRGB(int *rgbValues)
{
  for (byte i; i < 3; i++)
  {
    analogWrite(rgbLed[i], rgbValues[i]);
  }
}

void lcdClearLine(byte line)
{
  lcd.setCursor(0, line);
  lcd.print("                ");
  lcd.setCursor(0, line);
}

void showRGB(){
  char ch;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Show RGB");
  int rgbValues[3];  

  
  for (int i = 0; i < 3; i++)
  {
    int j = 0;
    int value = 0;
    lcdClearLine(1);
    lcd.print("Enter ");
    lcd.print(rgbChars[i]);
    lcd.print(": ");
    while (1)
    {
      do
      {
        ch = keypad.getKey();
      } while (!ch);
      if (ch != OK && j < 3)
      {
        int digit = ch - '0';
        value = value * 10 + digit;
        lcd.print(digit);
        j++;
      }
      else if (ch == OK)
        break;
    }
    rgbValues[i] = value;
  }

  lcd.clear();
  for (int i = 0; i < 3; i++)
  {
    lcd.print(rgbChars[i]);    
    lcd.print(rgbValues[i]);
    lcd.print(" ");
  }

  writeRGB(rgbValues);

  while (keypad.getKey() != OK)
    ;
}
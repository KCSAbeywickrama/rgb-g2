#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



int BLUE = 6;
int GREEN = 9;
int RED = 10;
int r, g, b;
String num;
int val;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  lcd.print("WELCOME");
  Serial.println("WELCOME");
}


void loop()
{

  char key = customKeypad.getKey();

  if (key == '*')
  {
    lcd.clear();
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    lcd.print("R value = ");
    Serial.print("R value = ");
  }

  if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'))
  {
    lcd.print(key);
    Serial.print(key);
    num = num + key;
  }

  else if (key == '#')
  {
    lcd.clear();
    val = num.toInt();
    lcd.print("value = ");
    Serial.println("value = ");
    lcd.print(val);
    Serial.print(val);
    lcd.setCursor(0, 1);
    lcd.print("R=/ G=x B=-");
    Serial.println("R=/ G=x B=-");
    num = "";
  }

  else if (key == 'A')
  {
    r = val;
    lcd.clear();
    lcd.print("G value = ");
    Serial.println("G value = ");
  }

  else if (key == 'B')
  {
    g = val;
    lcd.clear();
    lcd.print("B value = ");
    Serial.println("B value = ");
  }

  else if (key == 'C')
  {
    b = val;
    lcd.clear();
    lcd.print("press D ");
    Serial.print("press D ");
  }

  else if (key == 'D')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("R=");
    Serial.println("R=");
    lcd.print(r);
    Serial.print(r);
    lcd.setCursor(8, 0);
    lcd.print("G=");
    Serial.println("G=");
    lcd.print(g);
    Serial.print(g);
    lcd.setCursor(0, 1);
    lcd.print("B=");
    Serial.println("B=");
    lcd.print(b);
    Serial.print(b);

    analogWrite(RED, 255 - r);
    analogWrite(GREEN, 255 - g);
    analogWrite(BLUE, 255 - b);
    //delay (3000);
  }
}

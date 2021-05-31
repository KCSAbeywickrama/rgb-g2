//display libries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


int r_led = 2;
int g_led = 3;
int b_led = 4;
int ldr_p = A0;
int pwr = 5;
const int rgb_r = 9;
const int rgb_g = 10;
const int rgb_b = 11;

int red_val = 0, green_val = 0, blue_val = 0;
int p = 1;

void setup() {
  pinMode (r_led,OUTPUT);
  pinMode (g_led,OUTPUT);
  pinMode (b_led,OUTPUT);
  pinMode (pwr,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.backlight();
  digitalWrite(pwr,HIGH);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("processing...");
  lcd.setCursor(0,1);
  lcd.print("Please Wait.");
  
  for(int p = 1; p < 4 ; p=p+1){
    Serial.println(p);
    if(p == 1){
      digitalWrite(r_led,HIGH);
      for (int t=0; t<2000; t=t+100){
        red_val = analogRead(ldr_p);
        Serial.println(red_val);
        delay(100);
        }
      digitalWrite(r_led,LOW);
      }
    if(p==2){
      digitalWrite(g_led,HIGH);
      for (int t=0; t<2000; t=t+100){
        green_val = analogRead(ldr_p);
        Serial.println(green_val);
        delay(100);
        }
      digitalWrite(g_led,LOW);
      }
    if(p==3){
      digitalWrite(b_led,HIGH);
      for (int t=0; t<2000; t=t+100){
        blue_val = analogRead(ldr_p);
        Serial.println(blue_val);
        delay(100);
        }
      digitalWrite(b_led,LOW);
      }
   
  }
  calib(red_val,green_val,blue_val);
  Serial.println((String)red_val+","+ (String)green_val+"," + (String)blue_val);
  delay(3000);
  setColor(0,0,0);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(rgb_r, redValue);
  analogWrite(rgb_g, greenValue);
  analogWrite(rgb_b, blueValue);
}

void calib(int red_r, int green_r, int blue_r){
  const float R_max = 400;
  const float R_min = 150;
  const float G_max = 365;
  const float G_min = 98;
  const float B_max = 517;
  const float B_min = 175;
  
  int r_val = limit(red_r,R_max,R_min);
  int g_val = limit(green_r,G_max,G_min);
  int b_val = limit(blue_r,B_max,B_min);

  float m_r = 255.0/(R_max - R_min);
  float m_g = 255/(G_max - G_min);
  float m_b = 255/(B_max - B_min);

  r_val = (r_val - R_min)*m_r;
  g_val = (g_val - G_min)*m_g;
  b_val = (b_val - B_min)*m_b;
  setColor(r_val,g_val,b_val);
  Serial.println((String)r_val+","+ (String)g_val+"," + (String)b_val);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("color RGB val:");
  lcd.setCursor(0,1);
  lcd.print((String)r_val+","+ (String)g_val+"," + (String)b_val);

}

int limit (int _val, int _max, int _min){
  if (_val > _max){
    _val = _max;
  }
  else if (_val < _min){
    _val = _min;
  }
  return _val;
}

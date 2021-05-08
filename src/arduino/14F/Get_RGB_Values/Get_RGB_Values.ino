
int Red_max = 370;
int Green_max = 137;
int Blue_max = 105;
int red_pin = 10 ; 
int green_pin = 9 ; 
int blue_pin = 6 ;
char led;
int Sample_f_red;
int Sample_f_green;
int Sample_f_blue;

void setup() {
 
Serial.begin(9600);
Serial.println("Sample Please");
Serial.println("r or g or b");
pinMode(red_pin,OUTPUT);
pinMode(green_pin,OUTPUT);
pinMode(blue_pin,OUTPUT);

}
void loop() {
   if (Serial.available())
   {
    
    char led = Serial.read();
   
   if (led == 'r' )//on the red led.
   { 
    Serial.print("R value = ");
    setColor(0, 255, 255); // Red Color
    delay(3000);
    int Sample_ldr = analogRead(A0);
    delay(1000);
    //Serial.println ("analog read");
    //Serial.println(Sample_ldr);
    int Sample_f_red = map(Sample_ldr,0,Red_max,0,255);
    if (Sample_f_red > 255)
    {
      Sample_f_red = 255;
    }
    
    if (Sample_f_red < 0)
    {
      Sample_f_red = 0;
    }
    //Display Sample_f_r on LCD display.

    Serial.print(Sample_f_red);
    Serial.print("   ");
    delay(1000);
    setColor(255, 255, 255); 
    
    
   }
   
   else if (led == 'g')//on the green led.
   { 
    Serial.print("G value = ");
    setColor(255, 0, 255); // Green Color
    delay(3000);
    int Sample_ldr = analogRead(A0);
    delay(1000);
    //Serial.println("analog read");
    //Serial.println(Sample_ldr);
    int Sample_f_green = map (Sample_ldr,0,Green_max,0,255);
    if (Sample_f_green > 255)
    {
      Sample_f_green = 255;
    }
    if (Sample_f_green < 0)
    {
      Sample_f_green = 0;
    }
    //Display Sample_f_r on LCD display.

    Serial.print(Sample_f_green);
    Serial.print("   ");
    delay(1000);
    setColor(255, 255, 255); 
    
   }
   else if (led == 'b')//on the blue led.
   { 
    Serial.print("B value = ");
    setColor(255, 255, 0); // Blue Color
    delay(3000);
    int Sample_ldr = analogRead(A0);
    delay(1000);
    //Serial.println("analog read");
    //Serial.println(Sample_ldr);
    int Sample_f_blue = map(Sample_ldr,0,Blue_max,0,255);
    if (Sample_f_blue > 255)
    {
      Sample_f_blue = 255;
    }
    if (Sample_f_blue < 0)
    {
      Sample_f_blue = 0;
    }
    //Display Sample_f_r on LCD display.

    Serial.println(Sample_f_blue);
    delay(1000);
    setColor(255, 255, 255); 
   }
   }
   else
   {
    setColor(255, 255, 255);
   }
}
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(red_pin, redValue);
  analogWrite(green_pin, greenValue);
  analogWrite(blue_pin, blueValue);
}

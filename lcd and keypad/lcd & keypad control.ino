#include <LiquidCrystal.h>
#include <Keypad.h>

//lcd pins
int rs=13;
int en=12;
int d4=A0;
int d5=A1;
int d6=A2;
int d7=A3;

//input and output LED pins
int inputRed=9;
int inputGreen=10;
int inputBlue=11;
int outputRed=9;
int outputGreen=10;
int outputBlue=11;

int voltagePin=A4;    //LDR voltage read pin
int sensorPin=A5;     //input and output LED sensor pin

//Array variables
int inputColorArray[]={inputRed,inputGreen,inputBlue};
int outputColorArray[]={outputRed,outputGreen,outputBlue};
String colorStringArray[]={"R = ","G = ","B = "};
int colorValuesArray[]={0,0,0};
int colorPins[]={inputRed,inputGreen,inputBlue};
int outputColorPins[]={outputRed,outputGreen,outputBlue};
char *colorString[]={"R="," G=" ," B="};
int colorArray[]={0,0,0};
int whiteArray[]={0,0,0};
int blackArray[]={0,0,0};

//other variables
float colorVal;
float diffVal;
int delayTime=500;
int balance=false;
char loopKey='*';
char menuKey1;
char menuKey2;

//rows and columns of keypad
const byte rows=4;  
const byte columns=3;

//lcd and keypad
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
char keys[rows][columns]={
  {'1','2','3',},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows]={8,7,6,5};
byte columnPins[columns]={4,3,2};

Keypad inputKeypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);


//setup
void setup(){
  //output pins
  pinMode(inputRed,OUTPUT);
  pinMode(inputGreen,OUTPUT);
  pinMode(inputBlue,OUTPUT);
  pinMode(sensorPin,OUTPUT);
  digitalWrite(sensorPin,HIGH);

  //lcd activation and start
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  delay(5000);
  lcd.clear();
  
  //Serial.begin(9600);
}


//main loop
void loop(){  
  lcd.clear();

  //main menu for color sensor and given value RGB output
  if (loopKey=='*'){
    menuKey1='0';
    menuKey2='0';
    menuKey1=menu("Color Sensor = 1","Input RGB = 2",menuKey1);
  }
  lcd.clear();

  //color sensor
  if (menuKey1=='1'){
    //ask for input
    menuKey2=menu("Need calibration","Yes = 1  No = 2",menuKey2);
    //calibration
    if (menuKey2=='1'){
      lcd.clear();
      calibration();
    }
    //color sensing
    while (true){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Your color");  
      delay(2000);
      count(5);     
      RGBArray();     //get RGB readings
      calculation();    //calculation part
      lcd.clear();
      lcd.setCursor(0,0);
      printArray(colorArray);   //print RGB values
      lightRGB(colorArray);     //light up the RGB LED
      delay(1000);
      lcd.setCursor(0,1);
      //ask for continue or main menu
      lcd.print("sensor=#  menu=*");     
      loopKey='0';
      while (loopKey!='#' && loopKey!='*'){
        loopKey=inputKeypad.getKey();
      }      
      int blackValues[]={0,0,0};
      lightRGB(blackValues);
      if (loopKey=='*'){
        loop();
      }
    }
    
  }

  //given value RGB output 
  if (menuKey1=='2'){
    while (true){
      getValues(colorStringArray);    //ask for RGB inputs
      lightRGB(colorValuesArray);     //light up the RGB LED
      
      lcd.setCursor(0,0);
      lcd.print("Successful");
      delay(1000);
      lcd.setCursor(0,1);
      //ask for continue or main menu
      lcd.print("RGB= #  menu= *");
      loopKey='0';
      while (loopKey!='#' && loopKey!='*'){
        loopKey=inputKeypad.getKey();
      } 
      int blackValues[]={0,0,0};
      lightRGB(blackValues);
      if (loopKey=='*'){
        loop();
      }  
      
      lcd.clear();
    }
  }
  
  
}

//message printing and get input in menu
char menu(String row1,String row2,char Key){
  //printing messages for user
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(row1);
  lcd.setCursor(0,1);
  lcd.print(row2);

  //get input
  while(Key!='1' && Key!='2'){
      Key=inputKeypad.getKey();
  }
  delay(500);
  return Key;
  
}

//color caibration
void calibration(){
  //set calibration for white color
  lcd.print("White color");
  count(5);
  //make the RGB values for white color
  RGBArray();
  assignArray(whiteArray,colorArray);

  //set calibration for black color
  lcd.clear();
  lcd.print("Black color");
  count(5);
  //make the RGB values for white color
  RGBArray();
  assignArray(blackArray,colorArray); 
  //calibration finished 
  lcd.clear();
  balance=true;
  lcd.setCursor(0,0);
  lcd.print("   Calibrated   ");
  lcd.setCursor(0,1);
  lcd.print("  Successfully  ");
  delay(3000);
  lcd.clear();
}

//count before next function
void count(int Time){
  for (Time;Time>0;Time--){
    lcd.setCursor(0,1);
    lcd.print(Time);
    delay(1000);
  }
  lcd.setCursor(0,1);
  lcd.print("sensing...");
}

//get readings when LEDs light up
void RGBArray(){
  digitalWrite(sensorPin,LOW);
  for(int color=0;color<=2;color++){
    digitalWrite(colorPins[color],HIGH);
    delay(delayTime);

    float colorRead=0;
    for(int i=1;i<=50;i++){
      colorRead=colorRead+analogRead(voltagePin);
    }
    colorArray[color]=colorRead/50;   //average reading
    digitalWrite(colorPins[color],LOW);
    delay(delayTime);
  }  
  digitalWrite(sensorPin,HIGH);
}

//calculation part for color sensing
void calculation(){
    for(int color=0;color<=2;color++){
    diffVal=whiteArray[color] - blackArray[color];
    colorVal=(colorArray[color]-blackArray[color])/diffVal*255;

    if(colorVal>255){
      colorVal=255;
    }
    else if(colorVal<0){
      colorVal=0;
    }
    colorArray[color]=colorVal;
  }
}

//display RGB values in lcd
void printArray(int *valuesArray){
  for(int color=0;color<=2;color++){
    lcd.print(colorString[color]);
    lcd.print(valuesArray[color]);
  }
}

//get the input RGB values from user
void getValues(String *array){
      for(int color=0;color<=2;color++){
        lcd.setCursor(0,0);
        lcd.print("Enter values");
        lcd.setCursor(0,1);
        lcd.print(array[color]);
        char inputKey;
        String value="";
        while(true){
          inputKey=inputKeypad.getKey();
          String key=String(inputKey);
          if (inputKey=='#'){
            break;
        }
          if (inputKey!=NO_KEY){
            lcd.print(inputKey);
            value=value+key;
          }
        }
        int Val=value.toInt();
        //valid input
        if (Val>=0 && Val<=255){
          colorValuesArray[color]=Val;
        }
        //Invalid input
        else{
          lcd.clear();
          lcd.print("Invalid input");
          delay(2000);
          loopKey='0';
          loop();
        }
        lcd.clear();
      
      }
}

//light up the output RGB LED
void lightRGB(int *array){
      for(int color=0;color<=2;color++){
      analogWrite(outputColorArray[color],array[color]);
      }

}

/*void displayValues(int *array){
   lcd.setCursor(0,1);
   for (int color=0;color<=2;color++){
         lcd.print(array[color]);
   }
}*/

//assigning Arrays
void assignArray(int *array1,int *array2){
  for(int value=0;value<=2;value++){
    array1[value]=array2[value];
  }
}

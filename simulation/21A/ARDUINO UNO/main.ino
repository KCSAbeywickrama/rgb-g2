#include <LiquidCrystal.h>
#include <Keypad.h>

int rs=8;
int en=12;
int d4=13;
int d5=7;
int d6=A0;
int d7=A1;

int inputRed=A3;
int inputGreen=A4;
int inputBlue=A5;
int outputRed=9;
int outputGreen=10;
int outputBlue=11;

int inputColorArray[]={inputRed,inputGreen,inputBlue};
int outputColorArray[]={outputRed,outputGreen,outputBlue};
String colorStringArray[]={"R = ","G = ","B = "};
int colorValuesArray[]={0,0,0};

const byte rows=4;
const byte columns=3;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
char keys[rows][columns]={
  {'1','2','3',},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows]={0,1,2,3};
byte columnPins[columns]={4,5,6};

Keypad inputKeypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);


void setup(){
	lcd.begin(16,2);
	/*lcd.setCursor(0,0);
	lcd.print("Welcome");
	delay(5000);
	lcd.clear();*/
}

void loop(){
	
	lcd.clear();
	delay(500);
	getValues(colorStringArray);
	lightRGB(colorValuesArray);
	lcd.setCursor(0,0);
	lcd.print("Successfully");
	
	char inputKey='0';
	while(inputKey!='#'){
	    inputKey=inputKeypad.getKey();
	}
	lcd.clear();
	
	int blackValues[]={0,0,0};
	lightRGB(blackValues);
	
}


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
	    if (Val>=0 && Val<=255){
		  colorValuesArray[color]=Val;
	    }
	    else{
		  lcd.clear();
		  lcd.print("Invalid input");
		  delay(2000);
		  loop();
	    }
	    lcd.clear();
	    
      }
}

void lightRGB(int *array){
      for(int color=0;color<=2;color++){
	    analogWrite(outputColorArray[color],array[color]);
      }

}

void displayValues(int *array){
	 lcd.setCursor(0,1);
	 for (int color=0;color<=2;color++){
	       lcd.print(array[color]);
	 }
}

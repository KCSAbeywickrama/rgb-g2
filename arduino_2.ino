//RGB color pins
int redPin=8;
int greenPin=9;
int bluePin=10;

int voltagePin=A2;

float colorVal;
float diffVal;
int delayTime=500;
int balance=false;

//arrays
int colorPins[]={redPin,greenPin,bluePin};
char *colorString[]={"R = "," ,G = " ," B = "};
int colorArray[]={0,0,0};
int whiteArray[]={0,0,0};
int blackArray[]={0,0,0};


void setup(){
  //color pin outputs
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

  //Serial monitor
  Serial.begin(9600);
}

void loop(){
  if (balance==false){
    calibration();
  }

  Serial.println("hold a color paper");
  delay(delayTime*10);
  RGBArray();

  //calculation
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
  }M
  printArray(colorArray);
  delay(delayTime*20);
  
  
}

void calibration(){
  //set calibration for white color
  Serial.println("hold a white paper");
  delay(delayTime*10);

  RGBArray();
  assignArray(whiteArray,colorArray);

  //set calibration for black color
  Serial.println("hold a black paper");
  delay(delayTime*10);

  RGBArray();
  assignArray(blackArray,colorArray);
  balance=true;
  
}

void RGBArray(){
  for(int color=0;color<=2;color++){
    digitalWrite(colorPins[color],HIGH);
    delay(delayTime);

    float colorRead=0;
    for(int i=1;i<=5;i++){
      colorRead=colorRead+analogRead(voltagePin);
    }
    colorArray[color]=colorRead/5
    ;
    digitalWrite(colorPins[color],LOW);
    delay(delayTime);
  }
}

void assignArray(int *array1,int *array2){
  for(int value=0;value<=2;value++){
    array1[value]=array2[value];
  }
}

void printArray(int *valuesArray){
  for(int color=0;color<=2;color++){
    Serial.print(colorString[color]);
    Serial.print(valuesArray[color]);
  }
  Serial.println("");
  Serial.println("");
}

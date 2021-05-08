int r_led = 2;
int g_led = 3;
int b_led = 4;
int ldr_p = A0;

int red_val = 0, green_val = 0, blue_val = 0;
int p = 1;

void setup() {
  pinMode (r_led,OUTPUT);
  pinMode (g_led,OUTPUT);
  pinMode (b_led,OUTPUT);
  Serial.begin(9600);


}

void loop() {
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
  Serial.println((String)red_val+","+ (String)green_val+"," + (String)blue_val);
  delay(2000);
}

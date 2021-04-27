int r_led = 2;
int g_led = 3;
int b_led = 4;

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
      delay(500);
      digitalWrite(r_led,LOW);
      }
    if(p==2){
      digitalWrite(g_led,HIGH);
      delay(500);
      digitalWrite(g_led,LOW);
      }
    if(p==3){
      digitalWrite(b_led,HIGH);
      delay(500);
      digitalWrite(b_led,LOW);
      }
   
  }
}
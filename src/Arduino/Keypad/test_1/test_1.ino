
int q = 0
int num_in = ""
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);

}

void loop() {
  for (int p =0; p<=2; p++){
    digitalWrite(p+2,HIGH)
    if (digitalRead(5)==HIGH){
      int key = p+1
      }
    if (digitalRead(6)==HIGH){
      int key = p+4
      }
    if (digitalRead(7)==HIGH){
      int key = p+7
      }
    if (digitalRead(8)==HIGH){
      if (p==1){
        int key = 0
        }
      if (p==0){
        int key = "*"
        }
      if (p==2){
        int key = "#"
        }
      }
    if (p!="#"){
      num_in = num_in + (String)key
      }
    elif (p=="#"){
      int rgb_val = num_in
      if (q = 0){
        int r_val = rgb_val
        num_in = ""
        q += 1
        }
      if (q = 1){
        int g_val = rgb_val
        num_in = ""
        q += 1
        }
      if (q == 2){
        int b_val = rgb_val
        num_in = ""
        q += 1
        }
      }
    if (q==3){
      //display the value
      q = 0
      }
    if (key == "*"){
      //refresh the setup
      }
    
    }
}

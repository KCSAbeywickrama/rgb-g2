int r_ldr = A0;
int g_ldr = A1;
int b_ldr = A2;

int r_val = 0;
int g_val = 0;
int b_val = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  r_val = analogRead(r_ldr);
  g_val = analogRead(g_ldr);
  b_val = analogRead(b_ldr);
  Serial.println((String)r_val + "," + (String)g_val + "," + (String)b_val);
  delay(100);
  

}

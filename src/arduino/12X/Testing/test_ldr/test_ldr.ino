int ldr_p = A0;
int ldr_val = 0;
void setup() {
  Serial.begin(9600);


}

void loop() {
  ldr_val = analogRead(ldr_p);
  Serial.println(ldr_val);
  delay(100);

}

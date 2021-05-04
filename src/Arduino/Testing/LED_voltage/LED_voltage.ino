const int led_pin = 13;
const int v_read = A0;

void setup() {
  pinMode (led_pin,OUTPUT);
  pinMode (v_read,INPUT);
  Serial.begin(9600);
  digitalWrite(led_pin,HIGH);

}

void loop() {
  float val = analogRead(v_read);
  float val_1 = (val/1024.00)*5;
  Serial.println(val);
  Serial.println(val_1);
  delay(500);
}

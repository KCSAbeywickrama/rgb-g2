int light;


void setup() {
  Serial.begin(9600);
}

void loop() {
  light = analogRead(A0);
  Serial.println(light);
  delay(100);
}

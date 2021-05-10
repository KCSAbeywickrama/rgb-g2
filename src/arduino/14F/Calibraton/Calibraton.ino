int redPin= 7;
int greenPin = 6;
int bluePin = 5;


void setup() {
Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}


}
void loop() {
 int ldr = analogRead(A0);
 Serial.println(ldr);
 delay(1000);
}

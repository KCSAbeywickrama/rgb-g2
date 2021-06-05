void setup() {
  pinMode (A3,OUTPUT);
  pinMode (A4,OUTPUT);
  pinMode (A5,OUTPUT);
  pinMode (A2,INPUT);
  Serial.begin(9600);
    
   
}

void loop() {
  byte sensorLeds[3] = {A3, A4, A5};
  byte sensorLdr = A2;
  for (int led = 0; led < 3; led++)
    {
        Serial.println(led);
        digitalWrite(sensorLeds[led], 1);
        for (int time = 0; time < 5000; time += 100)
        {
            String data = String(time) + "," + String(analogRead(sensorLdr) * 10);
            Serial.println(data);
            delay(100);
        }
        digitalWrite(sensorLeds[led], 0);
        delay(3000);
    }

}

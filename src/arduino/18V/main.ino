void setup()
{
    Serial.begin(9600);
    Serial.println("Started");
    // initSensor();    
}
void loop()
{
// Serial.println("dataset1");
// showDataset1();
// Serial.println("dataset2");
// showDataset2();
Serial.println(analogRead(A5));
delay(500);
}
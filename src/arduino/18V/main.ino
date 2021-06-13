void setup()
{
    Serial.begin(115200);
    Serial.println("Started");
    initSensor();    
}
void loop()
{
Serial.println("dataset1");
showDataset1();
Serial.println("dataset2");
showDataset2();
}
void setup()
{
    Serial.begin(115200);
    Serial.println("Started");
    initSensor();    
}
void loop()
{ 
showDataset1();
showDataset2();
}
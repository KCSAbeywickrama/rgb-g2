void setup()
{
    Serial.begin(115200);
    Serial.println("Started");
    initSensor();
    showDataset();  
}

void loop()
{ 
 readColors();
 
}
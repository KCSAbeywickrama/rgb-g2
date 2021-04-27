void setup()
{
    Serial.begin(115200);
    Serial.println("Sensor Readings");
    initSensor();
}

void loop()
{ 
readColors();   
}
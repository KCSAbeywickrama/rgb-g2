void setup()
{
    Serial.begin(115200);
    Serial.println("Started");
    initSensor();
    calcCalibConst();
}
void loop()
{
    readColors();
}
byte sensorLeds[] = {A3, A4, A5};
byte sensorLdr = A2;
int i = 0;
int readings[] = {0, 0, 0};
void initSensor()
{
    for (byte pin : sensorLeds)
        pinMode(pin, OUTPUT);
}

void readSensor(int *readings)
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        delay(200);
        readings[i] = analogRead(sensorLdr);
        digitalWrite(sensorLeds[i], 0);
    }
}

void showReadings()
{
    readSensor(readings);
    for (int reading : readings)
    {
        Serial.print(reading);
        Serial.print(',');
    }
    Serial.println();
}
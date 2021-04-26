byte sensorLeds[] = {A4, A3, A5};
byte sensorLdr = A2;
int i = 0;
int readings[] = {0, 0, 0};
void initSensor()
{
    for (byte pin : sensorLeds)
        pinMode(pin, OUTPUT);
}

unsigned int analogAvgRead(byte pin, byte samples)
{
    unsigned int X = 0;
    unsigned long Y = 0;
    for (int i = 0; i < samples; i++)
    {
        delay(5);
        unsigned int x = analogRead(pin);
        X += x;
        Y += pow(x, 2);
    }
    unsigned int mean = X / samples;
    // unsigned long s = sqrt(Y / samples - pow(mean, 2));
    // Serial.print(s);
    // Serial.print('|');
    return mean;
}

void readSensor(int *readings)
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        delay(200);
        readings[i] = analogAvgRead(sensorLdr, 30);
        digitalWrite(sensorLeds[i], 0);
    }
}

void readAvgSensor(int *readings,byte samples)
{
    readings[0] = 0;
    readings[1] = 0;
    readings[2] = 0;
    for (int i = 0; i < samples; i++)
    {
        readSensor(readings);
    }
    for (int i = 0; i < 3; i++)
    {
        readings[i] /= samples;
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
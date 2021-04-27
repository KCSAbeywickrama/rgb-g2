byte sensorLeds[] = {A3, A4, A5};
byte sensorLdr = A2;
int i = 0;
int readings[] = {0, 0, 0};
int calib_data[][] = {{0, 0, 0}, {0, 0, 0};

void initSensor()
{
    pinMode(13, OUTPUT);
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

    Serial.println("Sensor Readings");
    for (int reading : readings)
    {
        Serial.print(reading);
        Serial.print(',');
    }
    Serial.println();
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

void blink()
{
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(13, 1);
        delay(500);
        digitalWrite(13, 0);
        delay(500);
    }
}

void calib()
{
    blink();
    readSensor(calib_data[0]);

    Serial.println("calib_data[0]");
    for (int reading : calib_data[0])
    {
        Serial.print(reading);
        Serial.print(',');
    }
    Serial.println();

    blink();
    readSensor(calib_data[1]);

    Serial.println("calib_data[1]");
    for (int reading : calib_data[1])
    {
        Serial.print(reading);
        Serial.print(',');
    }
    Serial.println();
}

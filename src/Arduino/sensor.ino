byte sensorLeds[] = {A3, A4, A5};
byte sensorLdr = A2;
int i = 0;
int readings[] = {0, 0, 0};
int colors[] = {0, 0, 0};
int calib_data[2][3] = {{416, 382, 327}, {77, 110, 89}};

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
    // Serial.println("Reading . . .");
    warm();
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        delay(200);
        readings[i] = analogAvgRead(sensorLdr, 30);
        digitalWrite(sensorLeds[i], 0);
    }

    // Serial.println("Readings");
    for (int i = 0; i < 3; i++)
    {
        Serial.print(readings[i]);
        Serial.print(',');
    }
    Serial.println();
}

void showReadings()
{

    readSensor(readings);

    readSensor(readings);
    readSensor(readings);
    Serial.println("Delay");
    delay(100);
    readSensor(readings);
    delay(500);
    readSensor(readings);
    delay(1000);
    readSensor(readings);
    delay(2000);
    readSensor(readings);
    delay(5000);
    readSensor(readings);
    Serial.println("end");
}
void warm(){
 for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        delay(200);
        int j = analogAvgRead(sensorLdr, 30);
        digitalWrite(sensorLeds[i], 0);
    }
}

void blink()
{
    // for (int i = 0; i < 10; i++)
    // {
    //     // digitalWrite(13, 1);
    //     delay(500);
    //     // digitalWrite(13, 0);
    //     delay(500);
    // }
}

void calib()
{
    Serial.println("Place on White");
    blink();
    readSensor(calib_data[0]);

    // Serial.println("calib_data[0]");
    // for (int reading : calib_data[0])
    // {
    //     Serial.print(reading);
    //     Serial.print(',');
    // }

    // Serial.println("\nPlace on Black");

    // blink();
    // readSensor(calib_data[1]);

    // Serial.println("calib_data[1]");
    // for (int reading : calib_data[1])
    // {
    //     Serial.print(reading);
    //     Serial.print(',');
    // }
    // Serial.println();
}

void calc(int *readings, int *colors)
{
    for (int i = 0; i < 3; i++)
        colors[i] = (float)(readings[i] - calib_data[1][i]) / (calib_data[0][i] - calib_data[1][i]) * 255;
}

void readColors()
{
    delay(1000);
    readSensor(readings);
    readSensor(readings);
    delay(2000);
    // calc(readings, colors);
    // for (int color : colors)
    // {
    //     Serial.print(color);
    //     Serial.print(',');
    // }
    // Serial.println();
}

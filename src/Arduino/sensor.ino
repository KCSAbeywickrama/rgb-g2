byte sensorLeds[3] = {A3, A4, A5};
byte sensorLdr = A2;
int i = 0;
int readings[3] = {0, 0, 0};
int colors[3] = {0, 0, 0};
int calibData[2][3] = {{654,387,318}, {331, 144, 104}};

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
        delay(100);
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
   
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        delay(2000);
        readings[i] = analogRead(sensorLdr);
        digitalWrite(sensorLeds[i], 0);
    }

    // Serial.println("Readings");
    printTriplet(readings);
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

void warm()
{
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
    Serial.println("Place on White");
    blink();
    readSensor(calibData[0]);
    Serial.println("calibData[0]");
    printTriplet(calibData[0]);

    Serial.println("\nPlace on Black");
    blink();
    readSensor(calibData[1]);
    Serial.println("calibData[1]");
    printTriplet(calibData[1]);
}

void calc(int *readings, int *colors)
{
    for (int i = 0; i < 3; i++)
    {
        colors[i] = (float)(readings[i] - calibData[1][i]) / (calibData[0][i] - calibData[1][i]) * 255;
        if (colors[i] > 255)
            colors[i] = 255;
        else if (colors[i] < 0)
            colors[i] = 0;
    }
}

void readColors()
{
    delay(500);
    readSensor(readings);
    calc(readings, colors);
    sendToColorDisp(colors);
}

void sendToColorDisp(int *colors)
{
    for (int i = 0; i < 3; i++)
    {
        Serial.print(colors[i]);
        Serial.print(",");
    }
    Serial.println(" ");
    Serial.println("---------");
}

void printTriplet(int *triplet)
{
    Serial.print(triplet[0]);
    Serial.print(',');
    Serial.print(triplet[1]);
    Serial.print(',');
    Serial.print(triplet[2]);
    Serial.println();
}

void showDataset()
{
    int color_sets[][3] = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {0, 0, 0},
        {127, 127, 127},
        {255, 255, 255},
        {255, 255, 0},
        {0, 255, 255},
        {255, 0, 255},
        {255, 127, 0},
        {50, 150, 220},
        {100, 30, 110}};

    for (int *set : color_sets)
    {
        printTriplet(set);
        blink();
        readSensor(readings);
        Serial.println();
    }
}

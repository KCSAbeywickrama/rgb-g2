byte sensorLeds[3] = {A3, A4, A5};
byte sensorLdr = A2;
int i = 0;
int readings[3] = {0, 0, 0};
int colors[3] = {0, 0, 0};

int calibColors[5][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {0, 0, 0}, {255, 255, 255}};
int calibData[5][3] = {{655, 120, 121}, {399, 233, 124}, {296, 156, 211}, {295, 94, 95}, {658, 335, 306}};
int calibConst[3][2];

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
    // printTriplet(readings);
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

void readCalibData()
{
    Serial.println("Calibarating...");
    for (int i = 0; i < 5; i++)
    {
        Serial.print("Place on ");
        printTriplet(calibColors[i]);
        blink();
        readSensor(calibData[i]);
    }
}

void calcCalibConst()
{
    for (int i = 0; i < 3; i++)
    {
        calibConst[i][1] = (calibData[i][i] * 3 + calibData[4][i]) / 4;
        calibConst[i][0] = (calibData[(i + 1) % 3][i] + calibData[(i + 2) % 3][i] + calibData[3][i] * 3) / 5;
    }
}


void calcColor(int *readings, int *colors)
{
    for (int i = 0; i < 3; i++)
    {
        colors[i] = (float)(readings[i] - calibConst[i][0]) / (calibConst[i][1] - calibConst[i][0]) * 255;
        if (colors[i] > 255)
            colors[i] = 255;
        else if (colors[i] < 0)
            colors[i] = 0;
    }
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
    Serial.println("Place...");
    delay(4000);
    readSensor(readings);
    calcColor(readings, colors);
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

void showDiff(){
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
        calcColor(readings, colors);
        printTriplet(colors);
        int diff[3];
        for(int i=0;i<3;i++)
        diff[i]=set[i]-colors[i];
        printTriplet(diff);
        Serial.println();
    }
}

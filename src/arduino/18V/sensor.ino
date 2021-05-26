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

unsigned int analogLastRead(byte pin, byte samples)
{
    unsigned int value;
    for (int i = 0; i < samples; i++)
    {
        delay(100);
        value = analogRead(pin);
    //     Serial.print(value);
    //     Serial.print('.');
    }
    // Serial.println();
    return value;
}

void readSensor(int *readings)
{
    // Serial.println("Reading . . .");

    for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        readings[i] = analogLastRead(sensorLdr, 20);
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
        int j = analogLastRead(sensorLdr, 30);
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
    Serial.println("Place...");
    delay(4000);
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

void showDataset(int dataset[][3], int count)
{
    for (int i = 0; i < count; i++)
    {
        printTriplet(dataset[i]);
        blink();
        readSensor(readings);
        Serial.println();
    }
}

void showDataset1()
{
    int dataset1[][3] = {
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

    showDataset(dataset1, 12);
}

void showDataset2()
{
    int dataset2[][3]{
        {204, 0, 0},
        {153, 0, 0},
        {102, 0, 0},
        {51, 0, 0},
        {255, 127, 0},
        {204, 102, 0},
        {153, 77, 0},
        {102, 52, 0},
        {51, 27, 0},
        {255, 255, 0},
        {204, 204, 0},
        {153, 153, 0},
        {102, 102, 0},
        {51, 51, 0},
        {0, 204, 0},
        {0, 153, 0},
        {0, 102, 0},
        {0, 51, 0},
        {0, 0, 204},
        {0, 0, 153},
        {0, 0, 102},
        {0, 0, 51},
        {75, 0, 130},
        {60, 0, 104},
        {45, 0, 78},
        {30, 0, 52},
        {15, 0, 26},
        {148, 0, 211},
        {118, 0, 169},
        {88, 0, 127},
        {58, 0, 85},
        {28, 0, 43},
        {204, 204, 204},
        {153, 153, 153},
        {102, 102, 102},
        {51, 51, 51},
    };

    showDataset(dataset2, 36);
}

void stableCheck()
{
    for (int led = 0; led < 3; led++)
    {
        Serial.println(led);
        digitalWrite(sensorLeds[led], 1);
        for (int time = 0; time < 5000; time += 100)
        {
            String data = String(time) + "," + String(analogRead(sensorLdr) * 10);
            Serial.println(data);
            delay(100);
        }
        digitalWrite(sensorLeds[led], 0);
        delay(3000);
    }
}

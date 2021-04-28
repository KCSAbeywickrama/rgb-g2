byte sensorLeds[] = {A3, A4, A5};
byte sensorLdr = A2;
int i = 0;
int readings[] = {0, 0, 0};
int colors[] = {0, 0, 0};
int calib_data[2][3] = {{482, 396, 332}, {165, 136, 102}};

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
    Serial.println("Reading . . .");
    warm();
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(sensorLeds[i], 1);
        delay(200);
        readings[i] = analogAvgRead(sensorLdr, 30);
        digitalWrite(sensorLeds[i], 0);
    }

    Serial.println("Readings");
    print_triplet(readings);    
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
    for (int i = 0; i < 10; i++)
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
    readSensor(calib_data[0]);
    Serial.println("calib_data[0]");
    print_triplet(calib_data[0]);    

    Serial.println("\nPlace on Black");
    blink();
    readSensor(calib_data[1]);
    Serial.println("calib_data[1]");
    print_triplet(calib_data[1]);
}

void calc(int *readings, int *colors)
{
    for (int i = 0; i < 3; i++)
    {
        colors[i] = (float)(readings[i] - calib_data[1][i]) / (calib_data[0][i] - calib_data[1][i]) * 255;
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
    send_to_colordisplay(colors);
}

void send_to_colordisplay(int *colors)
{
    for (int i = 0; i < 3; i++)
    {
        Serial.print(colors[i]);
        Serial.print(",");
    }
    Serial.println(" ");
    Serial.println("---------");
}

void print_triplet(int *triplet)
{
    Serial.print(triplet[0]);
    Serial.print(',');
    Serial.print(triplet[1]);
    Serial.print(',');
    Serial.print(triplet[2]);
    Serial.println();
}

void show_dataset()
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
        {100, 30, 110}
    }
    
}

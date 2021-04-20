int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
void setup()
{
    Serial.begin(9600);
    Serial.println(20);
}
void loop()
{
    readKey();
}

char readKey()
{
    //read row
    setDDR(0b11110000);
    writePORT(0b00001111);
    byte row = ~readPORT() & 0b00001111;

    //read column
    setDDR(0b00001111);
    writePORT(0b11110000);
    byte col = ~(readPORT() >> 4) & 0b00001111;

    if (row && col)
    {
        char ch = keys[getPos(row) - 1][getPos(col) - 1];
        Serial.println(ch);
        delay(500);
        return ch;
    }

    return 0;
}

byte getPos(byte value)
{
    byte pos = 0;
    while (value)
    {
        value /= 2;
        pos++;
    }
    return pos;
}

void setDDR(byte value)
{
    for (int pin : pins)
    {
        pinMode(pin, value % 2);
        value /= 2;
    }
}

void writePORT(byte value)
{
    for (int pin : pins)
    {
        digitalWrite(pin, value % 2);
        value /= 2;
    }
}

byte readPORT()
{
    byte value = 0;
    int i = 0;
    for (int pin : pins)
    {
        value += digitalRead(pin) << i;
        i++;
    }
    return value;
}
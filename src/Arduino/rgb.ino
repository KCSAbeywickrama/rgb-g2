#define OK '#'
#define MODE '*'

byte rgbLed[] = {9, 10, 11};
char rgbChars[] = {'R', 'G', 'B'};

void writeRGB(int *rgbValues)
{
    for (byte i = 0; i < 3; i++)
    {
        analogWrite(rgbLed[i], rgbValues[i]);
    }
}
void showRGB()
{

    char ch;
    int rgbValues[3];

    for (int i = 0; i < 3; i++)
    {
        int j = 0;
        int value = 0;

        Serial.print("\nEnter ");
        Serial.print(rgbChars[i]);
        Serial.print(": ");
        while (1)
        {
            do
            {
                ch = readKey();
            } while (!ch);
            if (ch != OK && j < 3)
            {
                int digit = ch - '0';
                value = value * 10 + digit;
                Serial.print(digit);
                j++;
            }
            else if (ch == OK)
                break;
        }
        rgbValues[i] = value;
    }

    Serial.println();
    for (int i = 0; i < 3; i++)
    {
        Serial.print(rgbChars[i]);
        Serial.print(":");

        Serial.print(rgbValues[i]);
        Serial.print(" ");
    }
    writeRGB(rgbValues);

    while (readKey() != OK)
        ;
}

#include "arm.h"

const int myservoPins[4] = {11, 12, 13, 14}; // 舵机引脚
int pos = 90;                                // variable to store the servo position
String comdata = "";
int numdata[4] = {0}, numdata1[4] = {122, 180, 180, 90}, mark = 0;

void servo_init(Servo &myservo)
{
    for (int i = 0; i < 4; i++)
    {
        myservo.attach(myservoPins[i], 100, 2500);
    }
}

void servo_command(Servo &myservo)
{
    int j = 0;
    while (Serial.available() > 0)
    {
        comdata += char(Serial.read());
        delay(2);
        mark = 1;
    }
    if (mark == 1)
    {
        Serial.println(comdata);
        Serial.println(comdata.length());
        for (int i = 0; i < comdata.length(); i++)
        {

            if (comdata[i] == ',')
            {
                j++;
            }
            else
            {
                numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
            }
        }
        comdata = String("");
        for (int i = 0; i < 4; i++)
        {
            if (numdata[i] == 0)
            {
                numdata[i] = numdata1[i];
            }
            Serial.print("Pin ");
            Serial.print(myservoPins[i]);
            Serial.print(" = ");
            Serial.println(numdata[i]);

            if ((numdata[i] - numdata1[i]) > 0)
            {
                for (pos = numdata1[i]; pos <= numdata[i]; pos += 1)
                {
                    myservo.write(myservoPins[i], pos);
                    delay(15);
                }
            }
            else
            {
                for (pos = numdata1[i]; pos >= numdata[i]; pos += -1)
                {
                    myservo.write(myservoPins[i], pos);
                    delay(15);
                }
            }

            // Servo_Sweep(i);
            numdata1[i] = numdata[i];
            numdata[i] = 0;
        }
        mark = 0;
    }
}
void Servo_Sweep(int data[4],Servo &myservo)
{
    for (int i = 0; i < 4; i++)
    {
        if (data[i] == 0)
        {
            data[i] = numdata1[i];
        }
        Serial.print("Pin ");
        Serial.print(myservoPins[i]);
        Serial.print(" = ");
        Serial.println(numdata[i]);

        if ((data[i] - numdata1[i]) > 0)
        {
            for (pos = numdata1[i]; pos <= data[i]; pos += 1)
            {
                myservo.write(myservoPins[i], pos);
                delay(15);
            }
        }
        else
        {
            for (pos = numdata1[i]; pos >= data[i]; pos += -1)
            {
                myservo.write(myservoPins[i], pos);
                delay(15);
            }
        }

        // Servo_Sweep(i);
        numdata1[i] = data[i];
        //data[i] = 0;
    }
}

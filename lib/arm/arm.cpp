#include "arm.h"

const int myservoPins[4] = {11, 12, 13, 14}; // 舵机引脚
int pos = 90;                                // variable to store the servo position
String comdata = "";
int numdata[3] = {0}, numdata1[3] = {0}, mark = 0;

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
        Kinematic_Analysis(numdata[0], numdata[1], numdata[2], myservo);
        Serial.println(numdata[0]);
        Serial.println(numdata[1]);

        // Servo_Sweep(i);
        for (int i = 0; i < 3; i++)
        {
            numdata1[i] = numdata[i];
            numdata[i] = 0;
        }
        mark = 0;
    }
}
void Servo_Sweep(int num, Servo &myservo)
{
    if ((numdata[num] - numdata1[num]) > 0)
    {
        for (pos = numdata1[num]; pos <= numdata[num]; pos += 1)
        {
            myservo.write(myservoPins[num], pos);
            delay(15);
        }
    }
    else
    {
        for (pos = numdata1[num]; pos >= numdata[num]; pos += -1)
        {
            myservo.write(myservoPins[num], pos);
            delay(15);
        }
    }
}
int Kinematic_Analysis(float x, float y, double pitch, Servo &myservo)
{
    int l0 = 105, l1 = 97, l2 = 170;
    //pitch = pitch * PI / 180;
    double Bx = x - l2 * cos(pitch);
    double By = y - l2 * sin(pitch);
    printf("%f %f\n", Bx, By);

    double cosbeta = (Bx * Bx + By * By + l0 * l0 - l1 * l1) / (2 * l0 * sqrt(Bx * Bx + By * By));
    printf("cosbeta = %f\n", cosbeta);

    double beta = acos(cosbeta) * 180 / PI;
    double alpha = atan2(By, Bx) * 180 / PI;
    double theta1 = alpha + beta;
    if (theta1 < 0)
    {
        theta1 = 0;
    }
    if (theta1 > 180)
    {
        theta1 = 180;
    }
    printf("theta1 = %f\n", theta1);

    double costheta2 = -(Bx * Bx + By * By - l0 * l0 - l1 * l1) / (2 * l0 * l1);
    double theta2 = -(180 - acos(costheta2) * 180 / PI);
    if (theta2 < -90)
    {
        theta2 = -90;
    }
    if (theta2 > 90)
    {
        theta2 = 90;
    }
    printf("theta2 = %f\n", theta2);

    printf("theta3 = %f\n", pitch * 180 / PI - theta1 - theta2);
    double theta3  =pitch * 180 / PI - theta1 - theta2;
    myservo.write(myservoPins[0], theta1);
    myservo.write(myservoPins[1], 90 - theta2);
    myservo.write(myservoPins[2], 90 - theta3);
    return 0;
}
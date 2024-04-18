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
        Kinematic_Analysis(numdata[0], numdata[1], 100, numdata[2], myservo);
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
int Kinematic_Analysis(float x, float y, float Beta, float Alpha, Servo &myservo)
{
    int l0 = 105, l1 = 97, l2 = 50;
    float m, n, k, a, b, c, theta1, theta2, theta3, s1ps2;
    m = l2 * cos(Alpha) - x;                          // 中间变量
    n = l2 * sin(Alpha) - y;                          // 中间变量
    k = (l1 * l1 - l0 * l0 - m * m - n * n) / 2 / l0; // 中间变量
    a = m * m + n * n;                                // 解一元二次方程
    b = -2 * n * k;
    c = k * k - m * m;

    if (b * b - 4 * a * c < 0)
        return 0; // 防止出现非实数解

    theta1 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a; // 得到一元二次方程的解，只取其中一个，另外一个解是(-b+sqrt(b*b-4*a*c))/2/a
    theta1 = asin(theta1) * 180 / PI;                // 弧度换成角度

    if (theta1 > 90)
        theta1 = 90; // 控制舵机的最大角度±90°
    if (theta1 < -90)
        theta1 = -90;

    k = (l0 * l0 - l1 * l1 - m * m - n * n) / 2 / l1; // 过程系数
    a = m * m + n * n;                                // 解一元二次方程
    b = -2 * n * k;
    c = k * k - m * m;

    if (b * b - 4 * a * c < 0)
        return 0; // 防止出现非实数解

    s1ps2 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a; // 得到一元二次方程的解，只取其中一个，另外一个解是(-b+sqrt(b*b-4*a*c))/2/a
    s1ps2 = asin(s1ps2) * 180 / PI;                 // 弧度换成角度

    if (s1ps2 > 90)
        theta2 = 90;
    if (s1ps2 < -90)
        theta2 = -90;

    theta2 = s1ps2 - theta1;
    if (theta2 > 90)
        theta2 = 90; // 控制舵机的最大角度±90°
    if (theta2 < -90)
        theta2 = -90; // 控制舵机的最大角度±90°

    theta3 = Alpha * 180 / PI - theta1 - theta2; // 求关节3角度
    if (theta3 > 90)
        theta3 = 90;
    if (theta3 < -90)
        theta3 = -90; // 控制舵机的最大角度±90°

    myservo.write(myservoPins[0], theta1 + 90);
    myservo.write(myservoPins[1], theta2 + 90);
    myservo.write(myservoPins[2], theta3 + 90);
    return 0;
}
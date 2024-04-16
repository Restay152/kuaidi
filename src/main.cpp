#include <Arduino.h>
#include <Servo.h>

static const int servosPins[4] = {11, 12, 13, 14}; // 舵机引脚
Servo servos[4];

int Sweep(int num);

int pos = 90; // variable to store the servo position
String comdata = "";
int numdata[4] = {90, 90, 90, 90}, numdata1[4] = {90, 90, 90, 90}, mark = 0;

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < 5; ++i)
  {
    if (!servos[i].attach(servosPins[i]))
    {
      Serial.print("Servo ");
      Serial.print(i);
      Serial.println("attach error");
    }
  }
}
void loop()
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
      Serial.print(servosPins[i]);
      Serial.print(" = ");
      Serial.println(numdata[i]);
      // servo[i].write(numdata[i]);
      Sweep(i);
      numdata1[i] = numdata[i];
      numdata[i] = 0;
    }
    mark = 0;
  }
}

int Sweep(int num)
{
  if ((numdata[num] - numdata1[num]) > 0)
  {
    for (pos = numdata1[num]; pos <= numdata[num]; pos += 1)
    {
      servos[num].write(pos);
      delay(15);
    }
  }
  else
  {
    for (pos = numdata1[num]; pos >= numdata[num]; pos += -1)
    {
      servos[num].write(pos);
      delay(15);
    }
  }
}

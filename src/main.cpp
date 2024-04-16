#include <Arduino.h>
#include <Servo.h>

int Sweep(int num);
Servo servo[4];
int pos = 90; // variable to store the servo position
String comdata = "";
int numdata[4] = {0}, numdata1[4] = {0}, PWMPin[] = {5, 6, 9, 10}, mark = 0;

void setup()
{
  Serial.begin(115200);
  servo[0].attach(9); // attaches the servo to the servo object
  servo[1].attach(10);
  servo[2].attach(6);
  servo[3].attach(5);
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
      Serial.print(PWMPin[i]);
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
      servo[num].write(pos);
      delay(15);
    }
  }
  else
  {
    for (pos = numdata1[num]; pos >= numdata[num]; pos += -1)
    {
      servo[num].write(pos);
      delay(15);
    }
  }
}
#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Servo.h>
extern int numdata[4];
extern int numdata1[4];
void servo_command(Servo &myservo);
void Servo_Sweep(int data[4],Servo& myservo);
#endif


/*
初始
122,180,180
抓取
59,149,159

131,64,74

*/


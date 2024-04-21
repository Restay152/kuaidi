#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Servo.h>

extern const int myservoPins[4];

void servo_command(Servo &myservo);
void Servo_Sweep(int num,Servo& myservo);
int Kinematic_Analysis(float x, float y, double pitch, Servo &myservo);
#endif


/*
Pin 11 = 63
Pin 12 = 139
Pin 13 = 146
Pin 14 = 68



*/


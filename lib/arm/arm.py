import math
l0=105
l1=97
l2=160
x =100
y =105
PI = math.pi
Alpha = PI/2
m =12*math.cos(Alpha)-x
n =12*math.sin(Alpha)-y
k = (l1 * l1 - l0 * l0 - m * m - n * n) / 2 / l0
a = m * m + n * n
b = -2 * n * k
c = k * k - m * m
if b*b -4*a*c < 0 :
    print("no")
theta1 = (-b + math.sqrt(b * b - 4 * a * c)) / 2 / a
theta1 = math.asin(theta1) * 180 / PI
if theta1 >90 :
    theta1 = 90
if theta1 <-90:
    theta1 = 90
k = (l0 * l0 - l1 * l1 - m * m - n * n) / 2 / l1
a= m * m + n * n
b = -2 * n * k
c = k * k - m * m
if b*b -4*a*c < 0 :
    print("no")
s1ps2 = (-b - math.sqrt(b * b - 4 * a * c)) / 2 / a
s1ps2 = math.asin(s1ps2) * 180 / PI
if s1ps2 > 90 :
    theta2 = 90
if s1ps2 <-90 :
    theta2 = -90
theta2=s1ps2-theta1
if theta2 > 90:
    theta2 = 90
if theta2 < -90:
    theta2 = -90
theta3 = Alpha * 180 / PI - theta1 - theta2
if theta3 > 90:
    theta3 = 90
if theta3 < -90:
    theta3 = -90
print(theta1)
print(theta2)
print(theta3)
print(l0*math.cos(theta1)+l1*math.cos(theta2+theta1)+l2*math.cos(theta1+theta2+theta3))
print(l0*math.sin(theta1)+l1*math.sin(theta2+theta1)+l2*math.sin(theta1+theta2+theta3))
print(theta1+theta2+theta3)
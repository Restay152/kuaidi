import math
l0=105
l1=97
l2=170
x =275
y =-97

PI = math.pi
pitch = 0
Bx = x - l2*math.cos(pitch)
By = y - l2*math.sin(pitch)
print("%f%f"%(Bx,By))
cosbeta = (Bx*Bx + By*By + l0*l0 - l1*l1)/(2*l0*math.sqrt(Bx*Bx+By*By))
print("cosbeta = %f"%cosbeta)
beta = math.acos(cosbeta)*180/PI
alpha = math.atan2(By,Bx)*180/PI
theta1 = alpha +beta
if theta1 < 0:
    theta1 = 0
if theta1 > 180:
    theta1 = 180
print("theta1 = %f"%(theta1))

costheta2 = -(Bx*Bx + By*By - l0*l0 - l1*l1)/(2*l0*l1)
theta2 = -(180 - math.acos(costheta2)*180/PI)
if theta2 < -90:
    theta2 =-90
if theta2 > 00:
    theta2 = 90
print("theta2 = %f"%(theta2))
print("theta3 = %f"%(pitch*180/PI-theta1-theta2))

#include <Arduino.h>
#include "mqtt.h"
#include "arm.h"

Servo myservo;
WiFiClient espclient;
PubSubClient client(espclient);

void setup()
{
  Serial.begin(115200);
  Serial.print("hello world");
  mqtt_init(espclient, client);
}
void loop()
{
  client.loop();
  //client.publish(topic,"shengyu");
  servo_command(myservo);
  Kinematic_Analysis(50,10,100,30,myservo);
  delay(3000);
  Kinematic_Analysis(10,20,100,90,myservo);
}



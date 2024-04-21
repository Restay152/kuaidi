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
  myservo.write(myservoPins[0],180);
  myservo.write(myservoPins[1],180);
  myservo.write(myservoPins[2],180);
  //Kinematic_Analysis(50,150,100,0,myservo);
}
void loop()
{
  client.loop();
  //client.publish(topic,"shengyu");
  servo_command(myservo);

  //delay(3000);

}



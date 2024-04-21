#include <Arduino.h>
#include "mqtt.h"
#include "arm.h"

Servo myservo;
WiFiClient espclient;
PubSubClient client(espclient);
int d0[4] = {122, 180, 180, 60};
int d1[4] = {59, 149, 159, 100};
int d2[4] = {131, 64, 74, 30};
String input = "";
String expectedData = "open";
void onReceiveFunction(void)
{
  // 接收串口1发送过来的数据长度
  size_t available = Serial1.available();

  // 显示接收长度
  Serial.printf("onReceive Callback:: There are %d bytes available: ", available);
  // 接收长度不为0则一直减
  while (available--)
  {
    // 通过串口0显示串口1接收到的数据
    Serial.print((char)Serial1.read());
  }
  // 显示换行
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 5, 6);
  pinMode(48, OUTPUT);
  Serial.print("hello world");
  mqtt_init(espclient, client);
  Servo_Sweep(d1, myservo);
  Serial.print("hello world");
}
void loop()
{
  client.loop();
  // client.publish(topic, "shengyu");
  servo_command(myservo);

  // delay(3000);
  // Servo_Sweep(d1, myservo);
  // delay(3000);
  // Servo_Sweep(d2, myservo);
  while (Serial1.available() > 0)
  {
    input += char(Serial1.read());
    delay(2); // 延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，
  }

  if (input.length() > 0)
  {
    Serial.println(input);
    if (input.equals(expectedData)) {
    Servo_Sweep(d1, myservo);
    delay(3000);
    Servo_Sweep(d2, myservo);
    delay(3000);
    Servo_Sweep(d0, myservo);
    }
    else
    {
      Serial.println("数据不相等！");
    }
    input = "";
  }
}

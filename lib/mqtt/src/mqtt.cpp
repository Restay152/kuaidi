#include "mqtt.h"

// wifi
const char *ssid = "CMCC-0721";
const char *password = "11111111";
// MQTT
bool ledState = false;
const char *mqtt_broker = "39.104.203.177";
const char *topic = "esp32/test";
const char *mqtt_username = "tester1";
const char *mqtt_password = "114514";
const int port = 1883;

// WiFiClient espclient;
// PubSubClient client(espclient);


// extern WiFiClient espclient;
// extern PubSubClient client(espclient);
void mqtt_init(WiFiClient& espclient, PubSubClient& client)
{

    // 使用 getWiFiClient 函数获取 espclient 对象

    // 断开之前的连接
    WiFi.disconnect(true);
    // 连接 Wi-Fi
    WiFi.begin(ssid, password);

    Serial.print("正在连接 Wi-Fi");

    // 检测是否链接成功
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("连接成功");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_broker, port);
    client.setCallback(callback);

    while (!client.connected())
    {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("Public emqx mqtt broker connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    client.publish(topic, "Hi EMQX I'm ESP32 ^^");
    client.subscribe(topic);
    // 使用板载 LED 反馈连接成功
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    String message;
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i]; // Convert *byte to string
    }
    Serial.print(message);
    if (message == "on" && !ledState)
    {
        digitalWrite(48, HIGH); // Turn on the LED
        ledState = true;
    }
    if (message == "off" && ledState)
    {
        digitalWrite(48, LOW); // Turn off the LED
        ledState = false;
    }
    Serial.println();
    Serial.println("-----------------------");
}
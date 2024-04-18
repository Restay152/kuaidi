#pragma once
#ifndef MQTT_H
#define MQTT_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

extern bool ledState;
extern const char *topic;
// extern WiFiClient espclient;
// extern PubSubClient client(espclient);
void mqtt_init(WiFiClient& espclient, PubSubClient& client);
void callback(char *topic, byte *payload, unsigned int length);
#endif //
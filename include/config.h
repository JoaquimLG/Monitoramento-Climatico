#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <DHT.h>
#include <WebServer.h>
#include <WiFi.h>

#define LEDVERMELHO 22
#define LEDAMARELO 21
#define DHTPIN 23        
#define DHTTYPE DHT11    
#define SENSORLUMINOSIDADE 35
#define POTENCIOMETRO 32

extern const char* nomeRede;
extern const char* senha;

extern WebServer server;
extern DHT dht;

extern float temperatura;
extern float umidade;
extern int valorLuminosidade;
extern int valorPotenciometro;

extern SemaphoreHandle_t xMutexGlobais;

#endif 
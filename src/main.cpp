#include "config.h"
#include "sensors.h"
#include "servidorWeb.h"
#include "ledControl.h"
#include "tasks.h"


//Aqui fica o nome da rede e senha
const char* nomeRede = "nomeRede";  
const char* senha = "senha"; 
IPAddress globalIP;

WebServer server(80);

//Cria o objeto do sensor de temperatura e umidade
DHT dht(DHTPIN, DHTTYPE);

float temperatura = 0.0;
float umidade = 0.0;
int valorLuminosidade = 0;
int valorPotenciometro = 0;

SemaphoreHandle_t xMutexGlobais;

void setup() {
  Serial.begin(115200);
  
  //Faz a chamada de todos os setups
  setupSensores();
  setupServidorWeb();
  setupLeds();

  xMutexGlobais = xSemaphoreCreateMutex();
  if(xMutexGlobais == NULL) {
    Serial.println("Não foi possível criar o mutex");
  }
  
  //Criação das tasks
  xTaskCreatePinnedToCore(vTaskLerSensores, "Task sensores", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(vTaskControleLeds, "Task controle de leds", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(vTaskServidorWeb, "Task servidor web", 4096, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(vTaskTelegram, "Task Telegram", 8192, NULL, 1, NULL, 1);

  Serial.println("Tasks iniciadas");

}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}

#include "config.h"
#include "sensors.h"
#include "servidorWeb.h"
#include "ledControl.h"
#include "tasks.h"


const char* nomeRede = "Esp-32";
const char* senha = "senha1210";

WebServer server(80);

//CRIA O OBJETO DO SENSOR DE TEMPERATURA E UMIDADE
DHT dht(DHTPIN, DHTTYPE);

//INICIALIZANDO AS VARIAVEIS
float temperatura = 0.0;
float umidade = 0.0;
int valorLuminosidade = 0;
int valorPotenciometro = 0;

SemaphoreHandle_t xMutexGlobais;

void setup() {
  Serial.begin(115200);
  
  setupSensores();
  setupServidorWeb();
  setupLeds();

  xMutexGlobais = xSemaphoreCreateMutex();
  if(xMutexGlobais == NULL) {
    Serial.println("Não foi possível criar o mutex");
  }
  
  //CRIAÇÃO DAS TASKS
  xTaskCreatePinnedToCore(vTaskLerSensores, "Task sensores", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(vTaskControleLeds, "Task controle de leds", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(vTaskServidorWeb, "Task servidor web", 4096, NULL, 2, NULL, 1);

  Serial.println("Tasks iniciadas");

}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}

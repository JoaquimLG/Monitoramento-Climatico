#include "config.h"
#include "sensors.h"
#include "servidorWeb.h"
#include "ledControl.h"


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

void setup() {
  Serial.begin(115200);
  
  setupSensores();
  setupServidorWeb();
  setupLeds();
  
}

void loop() {
  server.handleClient();

  lerSensores();
  atualizarLeds();

}

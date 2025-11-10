#include "ledControl.h"

void setupLeds() {
    pinMode(LEDAMARELO, OUTPUT);
    pinMode(LEDVERMELHO, OUTPUT);
}

void atualizarLeds() {
    //VERIFICA SE OS DADOS DE TEMPERATURA E UMIDADE FORAM RECEBIDOS CORRETAMENTE 
  if (!isnan(temperatura) && !isnan(umidade)) {
    if (temperatura > 30 || umidade < 40) { 
      digitalWrite(LEDVERMELHO, HIGH);
      vTaskDelay(pdMS_TO_TICKS(200));
      digitalWrite(LEDVERMELHO, LOW);
    }
  }

  if (valorLuminosidade < 1000) {
    digitalWrite(LEDAMARELO, HIGH);
  } else {
    digitalWrite(LEDAMARELO,LOW);
  }
}
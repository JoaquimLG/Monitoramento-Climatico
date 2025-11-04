#include "ledControl.h"

void setupLeds() {
    pinMode(LEDAMARELO, OUTPUT);
    pinMode(LEDVERMELHO, OUTPUT);
}

void atualizarLeds() {
    //VERIFICA SE OS DADOS DE TEMPERATURA E UMIDADE FORAM RECEBIDOS CORRETAMENTE 
  if (!isnan(temperatura) && !isnan(umidade)) {
    if (temperatura > 30 || umidade < 40) { 
      //VERIFICA SE OS VALORES ESTÃO ACIMA DO LIMITE E ACIONA UM LED VERMELHO
      digitalWrite(LEDVERMELHO, HIGH);
      delay(200);
      digitalWrite(LEDVERMELHO, LOW);
    }
  }

  if (valorLuminosidade > 300) {
    //VERIFICA O VALOR DO SENSOR DE LUMINOSIDADE, > 300 ACIONA O LED AMARELO
    digitalWrite(LEDAMARELO, HIGH);
  } else {
    digitalWrite(LEDAMARELO,LOW);
  }
}
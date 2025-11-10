#include "sensors.h"

void setupSensores() {
    dht.begin();

    pinMode(SENSORLUMINOSIDADE, INPUT);
    pinMode(POTENCIOMETRO, INPUT);
}

void lerSensores() {
    //Recebe os valores dos sensores
    temperatura = dht.readTemperature();
    umidade = dht.readHumidity();
    valorLuminosidade = analogRead(SENSORLUMINOSIDADE);
    valorPotenciometro = analogRead(POTENCIOMETRO);

    Serial.printf("Temperatura: %.1f\n", temperatura);
    Serial.printf("Umidade: %.1f\n", umidade);
    Serial.printf("Luminosidade: %d\n", valorLuminosidade);
    Serial.printf("Potenciometro: %d\n", valorPotenciometro);
    Serial.print("http://");
    Serial.println(globalIP);
    Serial.println("---------------------");
}
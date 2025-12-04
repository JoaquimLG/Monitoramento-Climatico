#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>

void vTaskLerSensores(void *pvparameters);
void vTaskControleLeds(void *pvparameters);
void vTaskServidorWeb(void *pvparameters);
void vTaskTelegram(void *pvparameters);

#endif
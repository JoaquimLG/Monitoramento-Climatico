#include "tasks.h"
#include "config.h"
#include "sensors.h"
#include "ledControl.h"
#include "telegramBot.h"

void vTaskLerSensores(void *pvparameters){
    (void) pvparameters;

    for(;;) {
        if(xSemaphoreTake(xMutexGlobais, portMAX_DELAY) == pdTRUE) {
            lerSensores();
            xSemaphoreGive(xMutexGlobais);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void vTaskControleLeds(void *pvparameters){
    (void) pvparameters;

    for(;;) {
        if(xSemaphoreTake(xMutexGlobais, portMAX_DELAY) == pdTRUE) {
            atualizarLeds();
            xSemaphoreGive(xMutexGlobais);
        }
        
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vTaskServidorWeb( void *pvparameters){
    (void) pvparameters;

    for(;;) {
        server.handleClient();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void vTaskTelegram( void *pvparameters){
    (void) pvparameters;

    // Aguarda conexão WiFi antes de começar a checar o bot
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    setupTelegram();

    for(;;) {
        verificarMensagensTelegram();
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}
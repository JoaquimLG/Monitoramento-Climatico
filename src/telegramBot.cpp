#include "telegramBot.h"

WiFiClientSecure clientSecure;
UniversalTelegramBot bot(BOT_TOKEN, clientSecure);

// Tempo para controle de requisições
unsigned long lastTimeBotRan = 0;
const int botRequestDelay = 1000; //Verificar a cada 1 segundo

void setupTelegram() {
    clientSecure.setInsecure();
    Serial.println("Telegram Bot configurado.");
}

String montarMensagemSensores() {
    float temp_local, umid_local;
    int luz_local, pot_local;

    // Acessa as variáveis globais de forma segura usando o Mutex
    if (xSemaphoreTake(xMutexGlobais, portMAX_DELAY) == pdTRUE) {
        temp_local = temperatura;
        umid_local = umidade;
        luz_local = valorLuminosidade;
        pot_local = valorPotenciometro;
        xSemaphoreGive(xMutexGlobais);
    } else {
        return "Erro: Não foi possível ler os sensores (Mutex travado).";
    }

    String msg = "Temperatura: " + String(temp_local, 1) + "\n";
    msg += "Umidade: " + String(umid_local, 1) + "\n";
    msg += "Luminosidade: " + String(luz_local) + "\n";
    msg += "Potenciometro: " + String(pot_local) + "\n";
    msg += "http://" + globalIP.toString() + "\n";
    msg += "---------------------";
    
    return msg;
}

void handleNewMessages(int numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
        String chat_id = bot.messages[i].chat_id;
        String text = bot.messages[i].text;
        String from_name = bot.messages[i].from_name;

        if (text == "/start") {
            String welcome = "Bem-vindo, " + from_name + ".\n";
            welcome += "Use o comando /get para ver os sensores.";
            bot.sendMessage(chat_id, welcome, "");
        }

        if (text == "/get") {
            String dados = montarMensagemSensores();
            bot.sendMessage(chat_id, dados, "");
        }
    }
}

void verificarMensagensTelegram() {
    if (millis() - lastTimeBotRan > botRequestDelay) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        
        while (numNewMessages) {
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        lastTimeBotRan = millis();
    }
}
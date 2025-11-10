#include "servidorWeb.h"

static void paginaPrincipal() {
    String html = R"rawliteral(
    <!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <title>Status Climático</title>
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.0/css/all.min.css">

  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }

    body {
      font-family: "Poppins", Arial, sans-serif;
      text-align: center;
      background: linear-gradient(135deg, #f7f9fc, #e9eef3);
      color: #333;
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: flex-start;
      overflow-x: hidden;
      animation: fadeIn 1s ease-in;
    }

    header {
      background: rgba(255, 255, 255, 0.3);
      padding: 25px;
      box-shadow: 0 4px 12px rgba(0,0,0,0.08);
      border-bottom-left-radius: 20px;
      border-bottom-right-radius: 20px;
      backdrop-filter: blur(10px);
      width: 100%;
      animation: slideDown 0.8s ease-out;
    }

    h1 {
      font-size: 30px;
      color: #2b2d42;
      letter-spacing: 1px;
      text-shadow: 0 2px 8px rgba(0,0,0,0.05);
    }

    .cards {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(230px, 1fr));
      gap: 25px;
      width: 90%;
      max-width: 900px;
      margin-top: 50px;
      animation: floatUp 0.9s ease-out;
    }

    .card {
      background: #fff;
      border-radius: 20px;
      padding: 30px 20px;
      box-shadow: 0 8px 25px rgba(0,0,0,0.1);
      transition: all 0.4s ease;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      position: relative;
    }

    .card:hover {
      transform: translateY(-8px) scale(1.03);
      box-shadow: 0 12px 30px rgba(0,0,0,0.15);
    }

    .card i {
      font-size: 40px;
      color: #3a86ff;
      margin-bottom: 15px;
      transition: transform 0.3s ease, color 0.3s;
    }

    .card:hover i {
      transform: rotate(-10deg) scale(1.1);
      color: #265df2;
    }

    .card h2 {
      font-size: 20px;
      margin-bottom: 10px;
      color: #2b2d42;
    }

    .card span {
      font-size: 22px;
      font-weight: bold;
      color: #3a86ff;
      transition: 0.3s;
    }

    .info-btn {
      position: absolute;
      top: 12px;
      right: 12px;
      cursor: pointer;
      background: none;
      border: none;
      padding: 6px;
      border-radius: 50%;
      transition: background 0.3s;
      z-index: 5;
    }

    .info-btn:hover {
      background: rgba(58, 134, 255, 0.1);
    }

    .info-btn svg {
      width: 20px;
      height: 20px;
      fill: #3a86ff;
      transition: fill 0.3s;
    }

    .info-btn:hover svg {
      fill: #265df2;
    }

    .info-card {
      position: absolute;
      top: 40px;
      right: 10px;
      background: #fff;
      border-radius: 12px;
      box-shadow: 0 4px 20px rgba(0,0,0,0.15);
      padding: 12px 15px;
      width: 180px;
      text-align: left;
      font-size: 14px;
      color: #333;
      opacity: 0;
      transform: translateY(-10px);
      pointer-events: none;
      transition: all 0.3s ease;
      z-index: 10;
    }

    .info-card.active {
      opacity: 1;
      transform: translateY(0);
      pointer-events: auto;
    }

    .info-card::after {
      content: "";
      position: absolute;
      top: -8px;
      right: 20px;
      border-left: 8px solid transparent;
      border-right: 8px solid transparent;
      border-bottom: 8px solid #fff;
    }

    @keyframes fadeIn {
      from { opacity: 0; }
      to { opacity: 1; }
    }

    @keyframes slideDown {
      from { transform: translateY(-50px); opacity: 0; }
      to { transform: translateY(0); opacity: 1; }
    }

    @keyframes floatUp {
      from { transform: translateY(50px); opacity: 0; }
      to { transform: translateY(0); opacity: 1; }
    }

    @media (max-width: 600px) {
      h1 {
        font-size: 24px;
      }
      .card {
        padding: 25px 15px;
      }
      .info-card {
        right: 50%;
        transform: translateX(50%) translateY(-10px);
        width: 160px;
      }
      .info-card::after {
        right: 50%;
        transform: translateX(50%);
      }
    }
  </style>
</head>

<body>
  <header>
    <h1><i class="fa-solid fa-cloud-sun"></i> Monitoramento Climático</h1>
  </header>

  <div class="cards">
    <div class="card">
      <button class="info-btn" data-sensor="Sensor DHT11">
        <svg viewBox="0 0 24 24"><path d="M12 2a10 10 0 1 0 10 10A10.011 10.011 0 0 0 12 2Zm0 17a1.25 1.25 0 1 1 1.25-1.25A1.251 1.251 0 0 1 12 19Zm1-4.75h-2v-6h2Z"/></svg>
      </button>
      <i class="fa-solid fa-temperature-half"></i>
      <h2>Temperatura</h2>
      <span id="temp">--</span> °C
      <div class="info-card"></div>
    </div>

    <div class="card">
      <button class="info-btn" data-sensor="Sensor DHT11">
        <svg viewBox="0 0 24 24"><path d="M12 2a10 10 0 1 0 10 10A10.011 10.011 0 0 0 12 2Zm0 17a1.25 1.25 0 1 1 1.25-1.25A1.251 1.251 0 0 1 12 19Zm1-4.75h-2v-6h2Z"/></svg>
      </button>
      <i class="fa-solid fa-droplet"></i>
      <h2>Umidade</h2>
      <span id="umid">--</span> %
      <div class="info-card"></div>
    </div>

    <div class="card">
      <button class="info-btn" data-sensor="Sensor de Luminosidade (LDR)">
        <svg viewBox="0 0 24 24"><path d="M12 2a10 10 0 1 0 10 10A10.011 10.011 0 0 0 12 2Zm0 17a1.25 1.25 0 1 1 1.25-1.25A1.251 1.251 0 0 1 12 19Zm1-4.75h-2v-6h2Z"/></svg>
      </button>
      <i class="fa-solid fa-sun"></i>
      <h2>Luminosidade</h2>
      <span id="luz">--</span>
      <div class="info-card"></div>
    </div>

    <div class="card">
      <button class="info-btn" data-sensor="Potenciômetro">
        <svg viewBox="0 0 24 24"><path d="M12 2a10 10 0 1 0 10 10A10.011 10.011 0 0 0 12 2Zm0 17a1.25 1.25 0 1 1 1.25-1.25A1.251 1.251 0 0 1 12 19Zm1-4.75h-2v-6h2Z"/></svg>
      </button>
      <i class="fa-solid fa-industry"></i>
      <h2>Poluição (simulada)</h2>
      <span id="pol">--</span> %
      <div class="info-card"></div>
    </div>
  </div>

  <script>
    document.querySelectorAll('.info-btn').forEach(btn => {
      btn.addEventListener('click', e => {
        const card = e.target.closest('.card');
        const infoCard = card.querySelector('.info-card');
        const text = btn.dataset.sensor;

        document.querySelectorAll('.info-card').forEach(c => {
          if (c !== infoCard) c.classList.remove('active');
        });

        infoCard.textContent = text;
        infoCard.classList.toggle('active');
      });
    });

    document.addEventListener('click', e => {
      if (!e.target.closest('.info-btn') && !e.target.closest('.info-card')) {
        document.querySelectorAll('.info-card').forEach(c => c.classList.remove('active'));
      }
    });

    // ===== NOVO SCRIPT PARA ATUALIZAR OS DADOS =====
    async function atualizarDados() {
      try {
        const resposta = await fetch("/dados");
        const dados = await resposta.json();

        if (!dados.erro) {
          document.getElementById("temp").textContent = dados.temperatura ?? "--";
          document.getElementById("umid").textContent = dados.umidade ?? "--";
          document.getElementById("luz").textContent = dados.luminosidade ?? "--";
          document.getElementById("pol").textContent = dados.poluicao ?? "--";
        }
      } catch (e) {
        console.error("Erro ao obter dados:", e);
      }
    }

    setInterval(atualizarDados, 3000);
    atualizarDados();
    // ==============================================
  </script>
</body>
</html>
)rawliteral";

    server.send(200, "text/html", html);
}

static void enviarDados() {
    String json = "{";

    float temp_local;
    float umid_local;
    int luz_local;
    int pot_local;

    if (xSemaphoreTake(xMutexGlobais, portMAX_DELAY) == pdTRUE) {
        temp_local = temperatura;
        umid_local = umidade;
        luz_local = valorLuminosidade;
        pot_local = valorPotenciometro;
        xSemaphoreGive(xMutexGlobais);
    } else {
        json = "{\"erro\":\"Recurso ocupado\"}";
        server.send(200, "application/json", json);
        return;
    }

    String temp_str = isnan(temp_local) ? "null" : String(temp_local, 1);
    String umid_str = isnan(umid_local) ? "null" : String(umid_local, 1);

    json += "\"temperatura\":" + temp_str + ",";
    json += "\"umidade\":" + umid_str + ",";
    json += "\"luminosidade\":" + String(luz_local) + ",";
    json += "\"poluicao\":" + String(pot_local) + "}";

    server.send(200, "application/json", json);
}

//CRIA O PONTO DE ACESSO E INICIALIZA O SERVIDOR WEB
void setupServidorWeb() {
    WiFi.softAP(nomeRede, senha);
    globalIP = WiFi.softAPIP();
    Serial.print("Endereço IP: ");
    Serial.println(globalIP);

    server.on("/", paginaPrincipal);
    server.on("/dados", enviarDados);
    server.begin();

    Serial.println("Servidor Web inicializado");
}
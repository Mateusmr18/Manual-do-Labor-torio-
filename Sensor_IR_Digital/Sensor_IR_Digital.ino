/*
 * PROJETO: Leitura de Sensor Infravermelho Digital (Ex: Módulo FC-51 / TCRT5000)
 * DESCRIÇÃO: Detecta a presença de obstáculos por meio da saída digital (DO) do sensor 
 * e aciona um LED indicador quando um objeto aproxima-se.
 */

// Definição dos pinos
#define PINO_IR 2       // Pino digital do Arduino conectado ao pino OUT/DO do sensor
#define PINO_LED 13     // LED indicador (utiliza o LED embutido no Arduino Uno)

void setup() {
  pinMode(PINO_IR, INPUT);      // Configura o pino do sensor como entrada de dados
  pinMode(PINO_LED, OUTPUT);    // Configura o pino do LED como saída
  Serial.begin(9600);           // Inicializa a comunicação Serial a 9600 bauds
}

void loop() {
  // Lê o sinal do sensor (retorna HIGH ou LOW)
  int estado_sensor = digitalRead(PINO_IR);

  /*
   * NOTA: A maioria dos módulos IR digitais operam em Lógica Invertida (Active LOW):
   * - LOW (0)  -> Obstáculo Detectado (luz IR refletida de volta)
   * - HIGH (1) -> Sem obstáculo (caminho livre)
   */
  if (estado_sensor == LOW) {
    digitalWrite(PINO_LED, HIGH);     // Acende o LED
    Serial.println("Status: Obstaculo DETECTADO!");
  } else {
    digitalWrite(PINO_LED, LOW);      // Apaga o LED
    Serial.println("Status: Caminho LIVRE");
  }

  delay(200); // Intervalo entre as leituras para evitar sobrecarga no Monitor Serial
}
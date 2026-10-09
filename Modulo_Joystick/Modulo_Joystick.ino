/*
 * PROJETO: Leitura de Módulo Joystick Analógico
 * DESCRIÇÃO: Exibe as coordenadas dos eixos X e Y e o estado do botão no Monitor Serial.
 */

// Mapeamento dos Pinos
#define PINO_X A0   // Eixo X no pino analógico A0
#define PINO_Y A1   // Eixo Y no pino analógico A1
#define PINO_SW 2   // Botão integrado no pino digital 2

void setup() {
  Serial.begin(9600);

  // Configura o pino do botão com resistor de PULL-UP interno do Arduino.
  // Sem pressionar = HIGH (1) | Pressionado = LOW (0)
  pinMode(PINO_SW, INPUT_PULLUP);
}

void loop() {
  // Lê os valores analógicos dos eixos (0 a 1023)
  int valor_X = analogRead(PINO_X);
  int valor_Y = analogRead(PINO_Y);

  // Lê o estado do botão (0 = pressionado, 1 = solto)
  int estado_botao = digitalRead(PINO_SW);

  // Exibe os dados formatados no Monitor Serial
  Serial.print("Eixo X: ");
  Serial.print(valor_X);
  Serial.print(" | Eixo Y: ");
  Serial.print(valor_Y);
  Serial.print(" | Botao: ");
  
  if (estado_botao == LOW) {
    Serial.println("PRESSIONADO");
  } else {
    Serial.println("SOLTO");
  }

  delay(200); // Pequeno intervalo para leitura legível no monitor
}
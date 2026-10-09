/*
 * =================================================================================
 * PROJETO: Controle de Módulo Relé
 * DESCRIÇÃO: Código para acionamento de módulo relé de 1 ou mais canais.
 * 
 * ATENÇÃO - LÓGICA INVERTIDA (ACTIVE LOW):
 * A grande maioria dos módulos relé para Arduino funciona com Lógica Invertida:
 * - LOW  (0V) -> LIGA o relé (fecha o contato)
 * - HIGH (5V) -> DESLIGA o relé (abre o contato)
 * 
 * ESQUEMA DE LIGAÇÃO DOS PINOS:
 * - VCC -> Pino 5V do Arduino
 * - GND -> Pino GND do Arduino
 * - IN  -> Pino Digital 7 do Arduino
 * =================================================================================
 */

// Define o pino digital conectado à entrada de sinal (IN) do relé
#define PINO_RELE 7

void setup() {
  // Configura a porta digital como saída
  pinMode(PINO_RELE, OUTPUT);

  // Garante que o relé inicie DESLIGADO (Devido à lógica invertida: HIGH = Desligado)
  digitalWrite(PINO_RELE, HIGH);

  Serial.begin(9600);
  Serial.println("Sistema de controle de relé iniciado.");
}

void loop() {
  // 1. Liga o relé
  Serial.println("Status: Relé LIGADO");
  digitalWrite(PINO_RELE, LOW);  // Envia 0V para acionar a bobina do relé
  delay(3000);                   // Mantém ligado por 3 segundos

  // 2. Desliga o relé
  Serial.println("Status: Relé DESLIGADO");
  digitalWrite(PINO_RELE, HIGH); // Envia 5V para desligar a bobina do relé
  delay(3000);                   // Mantém desligado por 3 segundos
}
/*
 * =================================================================================
 * PROJETO: Controle de Buzzer Ativo
 * DESCRIÇÃO: Como o buzzer ativo possui um oscilador interno, basta ligar 
 *            e desligar o pino com digitalWrite para emitir o bipe padrão.
 * 
 * LIGAÇÃO DOS PINOS:
 * - Pino (+) do Buzzer -> Pino Digital 8 do Arduino
 * - Pino (-) do Buzzer -> Pino GND do Arduino
 * =================================================================================
 */

#define PINO_BUZZER 8  // Define o pino digital onde o buzzer ativo está conectado

void setup() {
  // Configura o pino do buzzer como saída digital
  pinMode(PINO_BUZZER, OUTPUT);
}

void loop() {
  // Envia 5V para o buzzer: o circuito interno gera o apito automático
  digitalWrite(PINO_BUZZER, HIGH);
  delay(200); // Mantém o som ligado por 200 milissegundos

  // Corta a energia (0V): desliga o som
  digitalWrite(PINO_BUZZER, LOW);
  delay(800); // Mantém desligado por 800 milissegundos antes do próximo bipe
}
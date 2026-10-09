/*
 * =================================================================================
 * PROJETO: Controle de Buzzer Passivo
 * DESCRIÇÃO: Utiliza a função tone(pino, frequencia) para fazer a membrana do 
 *            buzzer vibrar em diferentes frequências, gerando notas/sons variados.
 * 
 * LIGAÇÃO DOS PINOS:
 * - Pino (+) do Buzzer -> Pino Digital 8 do Arduino
 * - Pino (-) do Buzzer -> Pino GND do Arduino
 * =================================================================================
 */

#define PINO_BUZZER 8  // Define o pino digital onde o buzzer passivo está conectado

void setup() {
  // Configura o pino do buzzer como saída
  pinMode(PINO_BUZZER, OUTPUT);
}

void loop() {
  // 1. Toca um tom grave (frequência de 440 Hz - Nota Lá) por 300 ms
  tone(PINO_BUZZER, 440);
  delay(300);

  // 2. Toca um tom médio (frequência de 880 Hz) por 300 ms
  tone(PINO_BUZZER, 880);
  delay(300);

  // 3. Toca um tom agudo (frequência de 1500 Hz) por 300 ms
  tone(PINO_BUZZER, 1500);
  delay(300);

  // Desliga o som do pino (obrigatório para interromper a frequência do buzzer passivo)
  noTone(PINO_BUZZER);
  
  // Aguarda 2 segundos antes de repetir a sequência
  delay(2000);
}
/*
 * =================================================================================
 * PROJETO: Contador de 0 a 9 no Display de 1 Dígito 5161AS (Cátodo Comum)
 * COMPATIBILIDADE: Arduino Uno e Arduino Mega
 * =================================================================================
 */

// Mapeamento dos pinos dos segmentos (A a G + Ponto Decimal DP)
const int pinoA  = 2;
const int pinoB  = 3;
const int pinoC  = 4;
const int pinoD  = 5;
const int pinoE  = 6;
const int pinoF  = 7;
const int pinoG  = 8;
const int pinoDP = 9;

// Array com os pinos de segmento para facilitar a varredura
const int pinosSegmentos[8] = {pinoA, pinoB, pinoC, pinoD, pinoE, pinoF, pinoG, pinoDP};

// Matriz de bytes que define quais segmentos acendem para cada número (0 a 9)
// Padrão de bits: B0 (A), B1 (B), B2 (C), B3 (D), B4 (E), B5 (F), B6 (G), B7 (DP)
const byte numeros[10] = {
  B00111111, // 0 -> A, B, C, D, E, F aceso
  B00000610, // 1 -> B, C aceso (0b00000110)
  B01011011, // 2 -> A, B, D, E, G aceso
  B01001111, // 3 -> A, B, C, D, G aceso
  B01100110, // 4 -> B, C, F, G aceso
  B01101101, // 5 -> A, C, D, F, G aceso
  B01111101, // 6 -> A, C, D, E, F, G aceso
  B00000111, // 7 -> A, B, C aceso
  B01111111, // 8 -> Todos os segmentos acesos
  B01101111  // 9 -> A, B, C, D, F, G aceso
};

void setup() {
  // Configura todos os pinos dos segmentos como SAÍDA
  for (int i = 0; i < 8; i++) {
    pinMode(pinosSegmentos[i], OUTPUT);
    digitalWrite(pinosSegmentos[i], LOW); // Inicia com o display apagado
  }
}

void loop() {
  // Conta de 0 a 9 exibindo cada número por 1 segundo
  for (int numero = 0; numero < 10; numero++) {
    exibirNumero(numeros[numero]);
    delay(1000);
  }
}

// Função auxiliar para acionar os segmentos com base na máscara de bits
void exibirNumero(byte mascara) {
  for (int i = 0; i < 8; i++) {
    // Lê se o bit i é 1 ou 0 e aciona o pino correspondente
    bool estadoSegmento = bitRead(mascara, i);
    digitalWrite(pinosSegmentos[i], estadoSegmento ? HIGH : LOW);
  }
}
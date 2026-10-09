/*
 * =================================================================================
 * PROJETO: Contador Multiplexado no Display 5641AS de 4 Dígitos (Cátodo Comum)
 * COMPATIBILIDADE: Arduino Uno e Arduino Mega
 * =================================================================================
 */

// Pinos dos Segmentos (Ânodos)
const int pinosSegmentos[7] = {2, 3, 4, 5, 6, 7, 8}; // A, B, C, D, E, F, G

// Pinos dos Dígitos (Cátodos Comuns)
const int pinosDigitos[4] = {9, 10, 11, 12}; // DIG1, DIG2, DIG3, DIG4

// Mapeamento dos números (0 a 9) em binário para Cátodo Comum (HIGH = Aceso)
const byte numeros[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

// Variáveis para controle do tempo sem travar o loop (Non-blocking delay)
unsigned long tempoAnterior = 0;
int contador = 0;

void setup() {
  // Configura os pinos de segmentos como SAÍDA
  for (int i = 0; i < 7; i++) {
    pinMode(pinosSegmentos[i], OUTPUT);
    digitalWrite(pinosSegmentos[i], LOW);
  }

  // Configura os pinos de dígitos como SAÍDA
  for (int i = 0; i < 4; i++) {
    pinMode(pinosDigitos[i], OUTPUT);
    digitalWrite(pinosDigitos[i], HIGH); // HIGH desliga o Cátodo Comum
  }
}

void loop() {
  // Incrementa o contador a cada 1 segundo (1000ms)
  if (millis() - tempoAnterior >= 1000) {
    tempoAnterior = millis();
    contador++;
    if (contador > 9999) contador = 0; // Reinicia após 9999
  }

  // Mantém a multiplexação continuamente ativa na tela
  exibirNumero4Digitos(contador);
}

// Função de Multiplexação (Exibe um número de até 4 dígitos)
void exibirNumero4Digitos(int valor) {
  int digitos[4];

  // Separa o valor numérico em 4 dígitos individuais
  digitos[0] = (valor / 1000) % 10; // Milhar (DIG1)
  digitos[1] = (valor / 100) % 10;  // Centena (DIG2)
  digitos[2] = (valor / 10) % 10;   // Dezena (DIG3)
  digitos[3] = valor % 10;          // Unidade (DIG4)

  // Varre os 4 dígitos rapidamente
  for (int d = 0; d < 4; d++) {
    // 1. Apaga todos os dígitos antes de trocar os segmentos
    for (int i = 0; i < 4; i++) {
      digitalWrite(pinosDigitos[i], HIGH); // HIGH = Cátodo Desligado
    }

    // 2. Coloca os estados corretos nos segmentos para o dígito atual
    for (int s = 0; s < 7; s++) {
      bool estadoSegmento = bitRead(numeros[digitos[d]], s);
      digitalWrite(pinosSegmentos[s], estadoSegmento ? HIGH : LOW);
    }

    // 3. Ativa o pino do dígito atual (LOW = Cátodo Ativo)
    digitalWrite(pinosDigitos[d], LOW);

    // 4. Pausa mínima para estabilização do brilho (~2ms)
    delay(2);

    // 5. Desliga o dígito atual
    digitalWrite(pinosDigitos[d], HIGH);
  }
}
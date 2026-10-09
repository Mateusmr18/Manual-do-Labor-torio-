/*
 * =================================================================================
 * PROJETO: Matriz de LEDs 8x8 (1588AS) Sem Driver MAX7219 (Ligação Direta)
 * DESCRIÇÃO: Controla a matriz por multiplexação (varredura rápida de linhas).
 *            Como não há driver dedicado, o Arduino acende uma linha por vez em
 *            alta velocidade, criando a ilusão de imagem contínua no olho humano.
 * 
 * COMPATIBILIDADE: Arduino Uno e Arduino Mega
 * =================================================================================
 */

// Mapeamento dos 8 Pinos das LINHAS (Anodos)
const byte pinosLinhas[8]  = {2, 3, 4, 5, 6, 7, 8, 9};

// Mapeamento dos 8 Pinos das COLUNAS (Catodos)
// Os pinos A0-A3 do Uno/Mega operam como saídas digitais normais
const byte pinosColunas[8] = {10, 11, 12, 13, A0, A1, A2, A3};

// Desenho 1: Coração
const byte CORACAO[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

// Desenho 2: Carinha Feliz (Smiley)
const byte SMILEY[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

void setup() {
  // Configura todos os 16 pinos como SAÍDA DIGITAL
  for (int i = 0; i < 8; i++) {
    pinMode(pinosLinhas[i], OUTPUT);
    pinMode(pinosColunas[i], OUTPUT);

    // Estado Inicial: Linhas em LOW (0V) e Colunas em HIGH (5V) -> Todos os LEDs apagados
    digitalWrite(pinosLinhas[i], LOW);
    digitalWrite(pinosColunas[i], HIGH);
  }
}

void loop() {
  // Exibe o Coração por 2000 milissegundos (2 segundos)
  exibirPadrao(CORACAO, 2000);

  // Exibe a Carinha Feliz por 2000 milissegundos (2 segundos)
  exibirPadrao(SMILEY, 2000);
}

/*
 * FUNÇÃO DE VARREDURA (MULTIPLEXAÇÃO):
 * Alterna rapidamente a ativação de cada linha (1 a 2 ms) para que a persistência
 * retiniana do olho humano perceba todos os LEDs acessos simultaneamente.
 */
void exibirPadrao(const byte padrao[8], unsigned long duracaoMs) {
  unsigned long tempoInicio = millis();

  // Mantém a varredura ativa durante o tempo especificado
  while (millis() - tempoInicio < duracaoMs) {
    for (int linha = 0; linha < 8; linha++) {
      
      // 1. Ativa a linha atual (Envia +5V para o Ânodo da linha)
      digitalWrite(pinosLinhas[linha], HIGH);

      // 2. Configura as colunas para a linha atual
      for (int coluna = 0; coluna < 8; coluna++) {
        // Extrai o bit correspondente à coluna no byte da linha (da esquerda p/ direita)
        bool ledAceso = bitRead(padrao[linha], 7 - coluna);

        if (ledAceso) {
          digitalWrite(pinosColunas[coluna], LOW);  // 0V no Cátodo acende o LED
        } else {
          digitalWrite(pinosColunas[coluna], HIGH); // 5V no Cátodo apaga o LED
        }
      }

      // 3. Tempo de exibição da linha atual (1ms de permanência)
      delay(1);

      // 4. Desliga a linha atual e reseta as colunas antes de ir para a próxima
      digitalWrite(pinosLinhas[linha], LOW);
      for (int coluna = 0; coluna < 8; coluna++) {
        digitalWrite(pinosColunas[coluna], HIGH);
      }
    }
  }
}
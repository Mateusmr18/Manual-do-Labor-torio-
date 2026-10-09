/*
 * =================================================================================
 * PROJETO: Leitura de Encoder Rotativo (Módulo KY-040)
 * DESCRIÇÃO: Detecta o sentido de rotação (Horário / Anti-horário), incrementa
 *            ou decrementa um contador de posição e lê o clique do botão integrado.
 * 
 * USO DE INTERRUPÇÕES:
 * Utiliza interrupções de hardware no pino CLK (Pino 2 no Uno/Mega) para garantir
 * que nenhum passo de rotação seja perdido durante a execução do programa.
 * =================================================================================
 */

// Mapeamento dos Pinos (Compatível com Arduino Uno e Mega)
#define PINO_CLK 2   // Pino de sinal A (Interrupção 0 - Pino 2 no Uno/Mega)
#define PINO_DT  3   // Pino de sinal B (Direção)
#define PINO_SW  4   // Botão integrado do encoder

// Variáveis globais para controle de rotação
// Note a palavra-chave 'volatile' para variáveis alteradas dentro de uma Interrupção (ISR)
volatile int contador = 0;
volatile int ultimoEstadoCLK;

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos de entrada
  pinMode(PINO_CLK, INPUT);
  pinMode(PINO_DT, INPUT);
  pinMode(PINO_SW, INPUT_PULLUP); // Ativa o resistor de pull-up para o botão

  // Grava o estado inicial do pino CLK
  ultimoEstadoCLK = digitalRead(PINO_CLK);

  // Configura a interrupção no pino CLK:
  // Executa a função 'atualizarEncoder()' toda vez que o sinal no PINO_CLK MUDAR (CHANGE)
  attachInterrupt(digitalPinToInterrupt(PINO_CLK), atualizarEncoder, CHANGE);

  Serial.println("Encoder Rotativo Inicializado.");
}

void loop() {
  // Exibe a posição atualizada do contador no Monitor Serial
  static int ultimoContador = 0;

  if (contador != ultimoContador) {
    Serial.print("Posição / Valor: ");
    Serial.println(contador);
    ultimoContador = contador;
  }

  // Leitura do botão integrado (Eixo central do encoder)
  if (digitalRead(PINO_SW) == LOW) {
    Serial.println("-> Botão Pressionado! (Resetando contador para 0)");
    contador = 0;
    
    // Debounce simples para evitar múltiplas leituras do clique
    delay(250); 
  }
}

/*
 * FUNÇÃO DE INTERRUPÇÃO (ISR)
 * É chamada automaticamente pelo hardware do Arduino quando ocorre uma borda de sinal no PINO_CLK.
 */
void atualizarEncoder() {
  int estadoAtualCLK = digitalRead(PINO_CLK);

  // Verifica se o pino CLK realmente mudou de estado
  if (estadoAtualCLK != ultimoEstadoCLK && estadoAtualCLK == LOW) {
    // Se o estado do pino DT for diferente do pino CLK, o encoder está girando no sentido HORÁRIO
    if (digitalRead(PINO_DT) != estadoAtualCLK) {
      contador++;
    } else {
      // Caso contrário, está girando no sentido ANTI-HORÁRIO
      contador--;
    }
  }

  ultimoEstadoCLK = estadoAtualCLK;
}
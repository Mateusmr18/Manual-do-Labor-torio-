/*
 * =================================================================================
 * PROJETO: Controle do Módulo LED RGB K85 1264
 * DESCRIÇÃO: Código com explicação detalhada para alternar cores no módulo RGB K85 1264
 *            (Cátodo Comum) utilizando a variação de sinal elétrico PWM no Arduino.
 * 
 * ESQUEMA DE LIGAÇÃO DOS PINOS:
 * - Pino '-' (GND)  -> Conectado à porta GND do Arduino
 * - Pino 'R' (Red)   -> Conectado à porta digital 9  (Porta PWM ~)
 * - Pino 'G' (Green) -> Conectado à porta digital 10 (Porta PWM ~)
 * - Pino 'B' (Blue)  -> Conectado à porta digital 11 (Porta PWM ~)
 * =================================================================================
 */

// Mapeamento das portas do Arduino que possuem suporte a PWM (marcadas com ~ na placa).
// O PWM simula uma saída de tensão variável entre 0V e 5V acionando rápida alternância de energia.
#define PINO_R 9   // Mapeia o pino 9 para controlar a cor Vermelha (Red)
#define PINO_G 10  // Mapeia o pino 10 para controlar a cor Verde (Green)
#define PINO_B 11  // Mapeia o pino 11 para controlar a cor Azul (Blue)

void setup() {
  // Configura os pinos definidos como SAÍDAS elétricas (OUTPUT).
  // O Arduino enviará energia a partir destas portas em direção aos pinos do módulo.
  pinMode(PINO_R, OUTPUT);
  pinMode(PINO_G, OUTPUT);
  pinMode(PINO_B, OUTPUT);
}

void loop() {
  // A função personalizada 'definirCor(R, G, B)' recebe 3 argumentos de intensidade (0 a 255).
  // 0 = Canal de cor completamente desligado (0V).
  // 255 = Canal de cor em brilho máximo (5V).

  // 1. Vermelho Puro
  definirCor(255, 0, 0);     
  delay(1000); // Mantém a cor por 1000 milissegundos (1 segundo)

  // 2. Verde Puro
  definirCor(0, 255, 0);     
  delay(1000);

  // 3. Azul Puro
  definirCor(0, 0, 255);     
  delay(1000);

  // 4. Mistura de Vermelho + Azul = Magenta(Púrpura)
  definirCor(255, 255, 0);   
  delay(1000);

  // 5. Mistura de Verde + Azul = Ciano
  definirCor(0, 255, 255);   
  delay(1000);

  // 6. Mistura de Vermelho + Verde = Amarelo
  definirCor(255, 0, 255);   
  delay(1000);

  // 7. Mistura de todas as 3 cores na potência máxima = Luz Branca
  definirCor(255, 255, 255); 
  delay(1000);

  // 8. Desliga todos os canais de cor
  definirCor(0, 0, 0);       
  delay(1000);
}

/*
 * FUNÇÃO AUXILIAR: definirCor
 * Recebe 3 inteiros referentes à intensidade de cada LED interno do módulo:
 * - int vermelho: nível de 0 a 255 para o LED vermelho
 * - int verde:    nível de 0 a 255 para o LED verde
 * - int azul:     nível de 0 a 255 para o LED azul
 */
void definirCor(int vermelho, int verde, int azul) {
  // O comando analogWrite envia uma onda PWM proporcional ao número de 0 a 255 informado.
  analogWrite(PINO_R, vermelho); // Ajusta o brilho do pino R
  analogWrite(PINO_G, verde);    // Ajusta o brilho do pino G
  analogWrite(PINO_B, azul);     // Ajusta o brilho do pino B
}
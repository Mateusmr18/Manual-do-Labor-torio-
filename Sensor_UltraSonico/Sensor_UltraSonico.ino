/*
 * =================================================================================
 * PROJETO: Leitura de Distância com Sensor Ultrassônico HC-SR04
 * BIBLIOTECA UTILIZADA: HCSR04 (por Martins Innus)
 * 
 * SOBRE O CRIADOR DA BIBLIOTECA:
 * A biblioteca <HCSR04.h> utilizada neste código foi desenvolvida por Martins Innus.
 * Ela simplifica o uso do sensor ultrassônico abstraindo o envio de pulsos do 
 * pino Trigger e a medição do tempo de resposta no pino Echo, fornecendo diretamente
 * funções prontas como measureDistanceCm().
 * =================================================================================
 */

// Inclui a biblioteca do sensor ultrassônico criada por Martins Innus
#include <HCSR04.h>

// Mapeamento dos pinos digitais no Arduino Uno
#define p_trigger 7  // Pino que envia o sinal ultrassônico (Trig)
#define p_echo 8     // Pino que recebe o eco do sinal ultrassônico (Echo)

/* 
// Mapeamento de pinos alternativo caso utilize o Arduino Mega
#define p_trigger 49
#define p_echo 47
*/

// Inicializa a classe UltraSonicDistanceSensor definindo o objeto 'distanceSensor'
// e associando os pinos definidos acima ao driver da biblioteca.
UltraSonicDistanceSensor distanceSensor(p_trigger, p_echo);

// Declaração das variáveis do tipo float (com casas decimais) 
// para evitar que divisões resultem em zero absoluto.
float dist_cm;
float dist_m;

void setup() {
  // Inicializa a comunicação Serial na velocidade de 9600 bauds
  // necessária para enviar dados ao Monitor Serial do computador.
  Serial.begin(9600);
}

void loop() {
  // Executa o método da biblioteca para medir a distância em centímetros.
  // Nota: O método retorna -1 se o sinal não voltar dentro do tempo limite.
  dist_cm = distanceSensor.measureDistanceCm();

  // Verifica se a medição é válida (diferente de -1)
  if (dist_cm < 0) {
    Serial.println("Erro: Sinal ultrassônico não retornado (verifique fiação/alimentação)");
  } else {
    // Converte centímetros em metros dividindo por 100.0 (float)
    dist_m = dist_cm / 100.0;

    // Imprime os dados formatados no Monitor Serial
    Serial.print("Distancia: ");
    Serial.print(dist_cm);
    Serial.print(" cm | ");
    Serial.print(dist_m, 2); // Exibe o valor em metros limitado a 2 casas decimais
    Serial.print(" m\n");
  }

  // Divisor visual para separar as leituras no Monitor Serial
  Serial.print("-----------------------\n");

  // Aguarda 1000 milissegundos (1 segundo) até a próxima leitura
  delay(1000); 
}
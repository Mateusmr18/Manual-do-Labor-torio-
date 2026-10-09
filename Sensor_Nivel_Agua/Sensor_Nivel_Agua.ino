/*
 * =================================================================================
 * PROJETO: Sensor de Nível de Água (Water Level Sensor)
 * DESCRIÇÃO: Lê o nível de líquido presente nas trilhas do sensor analógico
 *            e exibe o valor bruto (0 a 1023) junto com a classificação do nível.
 * 
 * ESQUEMA DE LIGAÇÃO DOS PINOS:
 * - (+) VCC -> Pino Digital 7 do Arduino (Alimentação sob demanda)
 * - (-) GND -> Pino GND do Arduino
 * - (S) SIG -> Pino Analógico A0 do Arduino
 * =================================================================================
 */

// Mapeamento dos Pinos
#define PINO_SENSOR A0  // Pino analógico para leitura do sinal de água (S / OUT)
#define PINO_POWER  7   // Pino digital para alimentar o sensor apenas durante a leitura

// Limites de calibração (Ajuste conforme os seus testes na água)
const int LIMITE_BAIXO = 100;
const int LIMITE_MEDIO = 300;
const int LIMITE_ALTO  = 500;

void setup() {
  Serial.begin(9600);

  // Configura o pino digital 7 como saída para alimentar o sensor sob demanda
  pinMode(PINO_POWER, OUTPUT);
  
  // Inicia com o sensor desligado
  digitalWrite(PINO_POWER, LOW);
}

void loop() {
  // 1. Liga o sensor apenas no momento da leitura (proteção contra corrosão)
  digitalWrite(PINO_POWER, HIGH);
  delay(10); // Aguarda 10ms para estabilizar a corrente elétrica nas trilhas

  // 2. Realiza a leitura analógica (Retorna valores entre 0 e 1023)
  int leitura = analogRead(PINO_SENSOR);

  // 3. Desliga a alimentação do sensor imediatamente após a medição
  digitalWrite(PINO_POWER, LOW);

  // 4. Exibe o valor bruto no Monitor Serial
  Serial.print("Leitura Analógica: ");
  Serial.print(leitura);
  Serial.print(" | Status: ");

  // 5. Interpretação dos níveis de água
  if (leitura < LIMITE_BAIXO) {
    Serial.println("SECO (Sem água)");
  } else if (leitura < LIMITE_MEDIO) {
    Serial.println("NÍVEL BAIXO");
  } else if (leitura < LIMITE_ALTO) {
    Serial.println("NÍVEL MÉDIO");
  } else {
    Serial.println("NÍVEL ALTO");
  }

  // Aguarda 1 segundo antes da próxima leitura
  delay(1000);
}
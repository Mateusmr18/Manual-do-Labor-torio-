/*
 * PROJETO: Leitura Analógica de Sensor (Ex: Sensor de Gás MQ)
 * DESCRIÇÃO: O código realiza a leitura contínua do sinal analógico fornecido por um
 * sensor conectado ao pino A0 e exibe o valor retornado no Monitor Serial.
 */

// Define o pino analógico A0 onde o pino de sinal do sensor está conectado
int PinA0 = A0;

// Limite (threshold) para acionamento de alarme (ex: Buzzer ou LED).
// Observação: Ajuste o valor conforme os testes de calibração do seu sensor.
int leitura_sensor = 300; 

void setup() {
  // Configura o pino A0 como entrada de dados (opcional para pinos analógicos, mas boa prática)
  pinMode(PinA0, INPUT);
  
  // Inicializa a comunicação Serial com taxa de transferência de 9600 bauds
  Serial.begin(9600);
}

void loop() {
  // Lê a tensão no pino A0 e a converte em um número inteiro entre 0 e 1023
  int valor_analogico = analogRead(PinA0);

  // Envia os dados formatados para o Monitor Serial do computador
  Serial.print("Leitura: ");
  Serial.print(valor_analogico);
  
  // Imprime uma linha divisória com quebra de linha (\n) para organizar a exibição
  Serial.print("\n-----------------------\n");

  // Aguarda 1000 milissegundos (1 segundo) antes de realizar a próxima leitura
  delay(1000);
}
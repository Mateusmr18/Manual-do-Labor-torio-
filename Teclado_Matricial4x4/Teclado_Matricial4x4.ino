/*
 * =================================================================================
 * PROJETO: Leitura de Teclado Matricial 4x4
 * COMPATIBILIDADE: Arduino Uno e Arduino Mega (usando os mesmos pinos D2 a D9)
 * BIBLIOTECA: <Keypad.h>
 * =================================================================================
 */

#include <Keypad.h>

// Definição do número de linhas e colunas do teclado
const byte LINHAS = 4;
const byte COLUNAS = 4;

// Mapeamento das teclas conforme o layout físico do teclado 4x4
char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Pinos conectados às LINHAS do teclado (R1, R2, R3, R4)
byte pinosLinhas[LINHAS] = {2, 3, 4, 5}; 

// Pinos conectados às COLUNAS do teclado (C1, C2, C3, C4)
byte pinosColunas[COLUNAS] = {6, 7, 8, 9}; 

// Inicializa a classe do teclado
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

void setup() {
  Serial.begin(9600);
  Serial.println("Teclado Matricial Inicializado. Pressione uma tecla...");
}

void loop() {
  // Lê se alguma tecla foi pressionada
  char teclaPressionada = teclado.getKey();

  // Se uma tecla for pressionada, exibe o valor na Serial
  if (teclaPressionada) {
    Serial.print("Tecla Pressionada: ");
    Serial.println(teclaPressionada);
  }
}
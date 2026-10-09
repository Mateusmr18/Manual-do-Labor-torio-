/*
 * =================================================================================
 * PROJETO: Controle de Motor de Passo (28BYJ-48) com Driver ULN2003
 * DESCRIÇÃO: Faz o motor de passo girar uma volta inteira no sentido horário,
 *            aguarda 1 segundo e faz uma volta completa no sentido anti-horário.
 * 
 * BIBLIOTECA: <Stepper.h> (Já vem instalada nativamente na IDE do Arduino)
 * =================================================================================
 */

#include <Stepper.h>

// Número total de passos por volta completa do motor 28BYJ-48
const int PASSOS_POR_VOLTA = 2048;

// Definição dos pinos conectados às entradas do Driver ULN2003
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Inicializa a biblioteca Stepper.
// NOTA IMPORTANTE DE SEQUÊNCIA: A ordem dos pinos na biblioteca deve ser (IN1, IN3, IN2, IN4)
// para respeitar a alternância das bobinas no driver ULN2003.
Stepper meuMotor(PASSOS_POR_VOLTA, IN1, IN3, IN2, IN4);

void setup() {
  // Define a velocidade do motor em RPM (Rotações Por Minuto)
  // Para o motor 28BYJ-48, a velocidade recomendada fica entre 5 e 15 RPM
  meuMotor.setSpeed(12);

  Serial.begin(9600);
  Serial.println("Motor de Passo Inicializado!");
}

void loop() {
  // 1. Gira 1 volta completa no sentido HORÁRIO (passos positivos)
  Serial.println("Girando: Sentido HORÁRIO");
  meuMotor.step(PASSOS_POR_VOLTA);
  delay(1000);

  // 2. Gira 1 volta completa no sentido ANTI-HORÁRIO (passos negativos)
  Serial.println("Girando: Sentido ANTI-HORÁRIO");
  meuMotor.step(-PASSOS_POR_VOLTA);
  delay(1000);
}
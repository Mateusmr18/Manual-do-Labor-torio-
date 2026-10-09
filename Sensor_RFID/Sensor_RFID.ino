/*
 * =================================================================================
 * PROJETO: Leitura de Tags/Cartões RFID com o Módulo RC522
 * BIBLIOTECA: <MFRC522.h> (por Miguel Balboa)
 * COMUNICAÇÃO: Barramento SPI
 * =================================================================================
 */

#include <SPI.h>
#include <MFRC522.h>

// Definição dos pinos de controle para o Arduino Uno
#define SS_PIN  10  // Pino Slave Select (SDA)
#define RST_PIN 9   // Pino Reset

// Para o Arduino Mega, você pode alterar o SS_PIN para 53 se preferir,
// mas manter no pino 10 também funciona perfeitamente.

// Instancia o objeto MFRC522
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  
  // Inicializa o barramento SPI
  SPI.begin();
  
  // Inicializa o leitor MFRC522
  rfid.PCD_Init();
  
  Serial.println("Módulo RFID RC522 Pronto!");
  Serial.println("Aproxime o cartão ou tag do leitor...");
  Serial.println("------------------------------------");
}

void loop() {
  // 1. Verifica se existe uma nova tag/cartão próximo ao leitor
  if (!rfid.PICC_IsNewCardPresent()) {
    return; // Se não houver cartão, interrompe a execução do loop aqui
  }

  // 2. Tenta selecionar e ler o cartão
  if (!rfid.PICC_ReadCardSerial()) {
    return; // Se falhar a leitura dos dados, interrompe o loop
  }

  // 3. Exibe a identificação única (UID) da tag no Monitor Serial
  Serial.print("Tag Detectada! UID:");
  
  // Imprime cada byte do UID em formato Hexadecimal (HEX)
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // 4. Finaliza a comunicação com a tag atual para liberar o leitor
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
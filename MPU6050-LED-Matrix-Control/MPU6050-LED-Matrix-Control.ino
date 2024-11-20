#include <Wire.h>
#include <MPU6050.h>

// Definição dos pinos do MAX7219
#define DIN_PIN 11  // Pino de dados
#define CS_PIN 10   // Pino de seleção de chip
#define CLK_PIN 12 // Pino de clock

MPU6050 mpu;

// Tabela para enviar dados à matriz
byte matrix[8] = {0}; // Representa o estado de cada linha (8x8)

// Função para enviar dados ao MAX7219
void sendToMax7219(byte address, byte data) {
  digitalWrite(CS_PIN, LOW);
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, address); // Endereço do registro
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);    // Dados
  digitalWrite(CS_PIN, HIGH);
}

// Inicialização do MAX7219
void initMax7219() {
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);

  sendToMax7219(0x09, 0x00); // Decodificação desligada
  sendToMax7219(0x0A, 0x03); // Brilho (0x00 a 0x0F)
  sendToMax7219(0x0B, 0x07); // Limite de varredura (todas as 8 linhas)
  sendToMax7219(0x0C, 0x01); // Liga o display
  sendToMax7219(0x0F, 0x00); // Teste desligado
}

// Atualiza os dados na matriz
void updateMatrix() {
  for (byte i = 0; i < 8; i++) {
    sendToMax7219(i + 1, matrix[i]);
  }
}

// Configuração inicial
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Inicializa o MPU6050
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 conectado com sucesso!");
  } else {
    Serial.println("Erro ao conectar com o MPU6050.");
    while (1); // Travar se falhar
  }

  // Inicializa o MAX7219
  initMax7219();
}

// Variáveis de posição do "pixel" na matriz
int xPos = 3;
int yPos = 3;

void loop() {
  int16_t ax, ay, az;

  // Obtém os valores de aceleração
  mpu.getAcceleration(&ax, &ay, &az);

  // Normaliza os valores (g = 16384)
  float x = ax / 16384.0;
  float y = ay / 16384.0;

  // Determina o movimento e ajusta as coordenadas
  if (x > 0.5 && xPos < 7) {
    Serial.println("DIREITA");
    xPos++; // Move para a direita
  } else if (x < -0.5 && xPos > 0) {
    Serial.println("ESQUERDA");
    xPos--; // Move para a esquerda
  }

  // Corrigindo o movimento vertical (Y)
  if (y > 0.5 && yPos < 7) {
    Serial.println("DESCER");
    yPos++; // Agora desce na matriz
  } else if (y < -0.5 && yPos > 0) {
    Serial.println("SUBIR");
    yPos--; // Agora sobe na matriz
  }

  // Atualiza a posição do "pixel" na matriz
  for (int i = 0; i < 8; i++) {
    matrix[i] = 0; // Limpa a linha
  }
  matrix[yPos] = 1 << xPos; // Acende o "pixel" na posição correta

  updateMatrix(); // Envia os dados para a matriz

  delay(100); // Pequeno atraso para suavizar o movimento
}

#include <Arduino.h>


const int botao1 = 2;
const int botao2 = 3;
const int botao3 = 4;
const int botao4 = 5;

const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;

void setup() {
  Serial.begin(9600); // Inicializa comunicação serial
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(botao4, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  int estado = 0;

  if (digitalRead(botao1) == LOW) estado += 1;
  if (digitalRead(botao2) == LOW) estado += 2;
  if (digitalRead(botao3) == LOW) estado += 4;
  if (digitalRead(botao4) == LOW) estado += 8;

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  switch (estado) {
    case 0: Serial.println("Nenhum botão pressionado"); break;
    case 1: digitalWrite(led1, HIGH); Serial.println(" cima"); break;
    case 2: digitalWrite(led2, HIGH); Serial.println("baixo "); break;
    case 3: digitalWrite(led1, HIGH); digitalWrite(led2, HIGH); Serial.println("cima e baixo"); break;
    case 4: digitalWrite(led3, HIGH); Serial.println("direita"); break;
    case 5: digitalWrite(led1, HIGH); digitalWrite(led3, HIGH); Serial.println("cima e direita"); break;
    case 6: digitalWrite(led2, HIGH); digitalWrite(led3, HIGH); Serial.println("baixo e direita"); break;
    case 7: digitalWrite(led1, HIGH); digitalWrite(led2, HIGH); digitalWrite(led3, HIGH); Serial.println("cima, baixo e direita"); break;
    case 8: digitalWrite(led4, HIGH); Serial.println("esquerda"); break;
    case 9: digitalWrite(led1, HIGH); digitalWrite(led4, HIGH); Serial.println("cima e esquerda"); break;
    case 10: digitalWrite(led2, HIGH); digitalWrite(led4, HIGH); Serial.println("baixo e esquerda"); break;
    case 11: digitalWrite(led1, HIGH); digitalWrite(led2, HIGH); digitalWrite(led4, HIGH); Serial.println("cima, baixo e esquerda"); break;
    case 12: digitalWrite(led3, HIGH); digitalWrite(led4, HIGH); Serial.println("direita e esquerda"); break;
    case 13: digitalWrite(led1, HIGH); digitalWrite(led3, HIGH); digitalWrite(led4, HIGH); Serial.println("cima, direita e esquerda"); break;
    case 14: digitalWrite(led2, HIGH); digitalWrite(led3, HIGH); digitalWrite(led4, HIGH); Serial.println(" baixo, direita e esquerda"); break;
    case 15: digitalWrite(led1, HIGH); digitalWrite(led2, HIGH); digitalWrite(led3, HIGH); digitalWrite(led4, HIGH); Serial.println("Todos os botões"); break;
  }

  delay(200); 
}
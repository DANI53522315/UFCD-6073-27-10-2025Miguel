#include <Arduino.h>
#include <HCSRO4_attachInterrupt.h>


// Definição dos pinos do Sensor HC-SR04
#define TRIG_PIN A1
#define ECHO_PIN A0

// Definição dos Pinos dos LEDs
const int LED_VERMELHO = 4; // Indica "Muito Perto"
const int LED_AMARELO = 5;  // Indica "Distância Média"
const int LED_VERDE = 6;    // Indica "Longe"

// --- Configurações das Faixas de Distância (Valores em centímetros) ---
const float LIMITE_PERTO = 10.0; // Perto: abaixo de 10 cm (Acende LED Vermelho)
const float LIMITE_MEDIO = 30.0; // Médio: entre 10 cm e 30 cm (Acende LED Amarelo)
const float MAX_DISTANCIA = 250.0; // Distância máxima para considerar uma leitura válida

// Timeout para pulseIn em micros (suficiente para medir até ~300 cm)
const unsigned long PULSE_TIMEOUT = 30000UL;

void setup() {
  // Inicializa a comunicação serial a 9600 bauds
  Serial.begin(9600);
  
  // Configura os pinos do sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Configura os pinos dos LEDs como SAÍDA e os desliga
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);
  
  Serial.println("--- Sensor Ultrassonico com LEDs Ativo ---");
}

float measureDistanceCm() {
  // Gera pulso de trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lê a duração do pulso de retorno em micros
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);
  if (duration == 0) {
    // sem leitura (timeout)
    return 0.0;
  }
  // Converte tempo (us) para distância em cm (aprox 58 us por cm ida+volta)
  float distance = duration / 58.0;
  return distance;
}

void loop() {
  // 1. --- Medição da Distância ---
  float distance = measureDistanceCm(); 
  
  // 2. --- Lógica de Controle dos LEDs e Saída Serial ---
  // Desliga todos os LEDs no início de cada ciclo para garantir que apenas um acenda
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);

  Serial.print("Distancia: ");

  if (distance == 0.0 || distance > MAX_DISTANCIA) {
    // Caso de erro de leitura ou fora do alcance
    Serial.println("Objeto fora do alcance ou erro de leitura.");
  } else if (distance <= LIMITE_PERTO) {
    // Muito Perto (<= 10 cm)
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.print("PERTO (ALERTA!) - ");
    Serial.print(distance);
    Serial.println(" cm");
  } else if (distance <= LIMITE_MEDIO) {
    // Distância Média (> 10 cm e <= 30 cm)
    digitalWrite(LED_AMARELO, HIGH);
    Serial.print("MÉDIO - ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    // Longe (> 30 cm)
    digitalWrite(LED_VERDE, HIGH);
    Serial.print("LONGE (Seguro) - ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // 3. --- Pausa ---
  // Aguarda 500 milissegundos antes da próxima leitura
  delay(500);
}




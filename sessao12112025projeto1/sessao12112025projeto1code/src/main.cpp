#include <Arduino.h>

// --- Definição dos Pinos ---
// HC-SR04
const int pin_trigger = 9; // Pino Trigger do HC-SR04 (Saída)
const int pin_echo = 10;   // Pino Echo do HC-SR04 (Entrada)

// LDR (Sensor de Luminosidade)
const int pin_ldr = A0;    // Pino Analógico para o LDR

// --- Variáveis para Millis ---
// Ultrassônico
unsigned long tempo_anterior_us = 0; // Armazena o último momento que o US foi medido
const long intervalo_us = 500;       // Intervalo de medição do US em ms (0.5 segundo)

// LDR
unsigned long tempo_anterior_ldr = 0; // Armazena o último momento que o LDR foi medido
const long intervalo_ldr = 100;      // Intervalo de medição do LDR em ms (0.1 segundo)

// --- Protótipos das Funções ---
long medirDistancia();
void lerLDR();

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Configura os pinos do HC-SR04
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);

  // Configura o pino do LDR (como é analógico, não precisa de pinMode específico)
}

void loop() {
  unsigned long tempo_atual = millis();

  // --- Leitura do Sensor Ultrassônico (HC-SR04) ---
  // Verifica se o intervalo de 500ms passou
  if (tempo_atual - tempo_anterior_us >= intervalo_us) {
    // Salva o tempo atual como o último momento em que a leitura foi feita
    tempo_anterior_us = tempo_atual;

    long distancia = medirDistancia();

    // Imprime a distância na Serial
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }

  // --- Leitura do Sensor de Luminosidade (LDR) ---
  // Verifica se o intervalo de 100ms passou
  if (tempo_atual - tempo_anterior_ldr >= intervalo_ldr) {
    // Salva o tempo atual como o último momento em que a leitura foi feita
    tempo_anterior_ldr = tempo_atual;

    lerLDR();
  }

  // Outras tarefas que não dependem do tempo podem ser executadas aqui
}

// --- Funções de Leitura ---

/**
 * Função para medir a distância usando o HC-SR04.
 * Retorna a distância em centímetros (long).
 */
long medirDistancia() {
  // Garante que o pino Trig está em LOW
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);

  // Dispara o pulso no Trig (nível HIGH por 10 microsegundos)
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);

  // Mede a duração do pulso de retorno (Echo) em microsegundos
  long duracao = pulseIn(pin_echo, HIGH);

  // Converte a duração em distância (cm)
  // Distância = (Duração do pulso * Velocidade do som) / 2
  // Velocidade do som (aprox.): 0.0343 cm/µs
  // Distância = duração * 0.0343 / 2
  long distancia_cm = duracao * 0.034 / 2;

  return distancia_cm;
}

/**
 * Função para ler o valor do LDR e imprimir na Serial.
 */
void lerLDR() {
  int valor_ldr = analogRead(pin_ldr);

  // Imprime o valor do LDR na Serial
  Serial.print("LDR (Luminosidade): ");
  Serial.println(valor_ldr);
}
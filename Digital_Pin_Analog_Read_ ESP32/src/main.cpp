#include <Arduino.h>

#define READ_PIN 18
#define PULSE_PIN 19
const uint32_t  ANALOG_TIMEOUT  = 500;  // = 20ms 20000

void setup() {
  Serial.begin(115200);
  pinMode(READ_PIN,   INPUT);
  pinMode(PULSE_PIN,  OUTPUT);

  pinMode(22,  OUTPUT);
  pinMode(23,   INPUT);
  
}//end setup

uint8_t analogDigitalRead(const uint8_t Ppin, const uint8_t Rpin) {
  // Envia pulso
  digitalWrite(Ppin, HIGH);
  uint32_t us = micros();

  // Aguarda carga do capacitor
  while ((micros() - us) < ANALOG_TIMEOUT && digitalRead(Rpin) == LOW);

  // Obtem tempo de carga
  us = micros() - us;

  // Coloca pino em nível baixo para descarga do capacitor
  digitalWrite(Ppin, LOW);

  // Aguarda descarga (= Tau x 5)
  delay(ANALOG_TIMEOUT / 1000 * 5); // Tempo em ms

  // Verifica valor lido
  if (us > ANALOG_TIMEOUT) {
    // Timeout
    us = ANALOG_TIMEOUT;
  }
  
  // Calcula leitura (0% a 100%)
  return uint8_t(us * 100 / ANALOG_TIMEOUT);
}//end analogDigitalRead

void loop() {
  uint8_t adc = analogDigitalRead(PULSE_PIN, READ_PIN);
  uint8_t adc2 = analogDigitalRead(22,23);

  Serial.print(adc);
  Serial.print(" ");
  Serial.print(adc2);
  Serial.println("");
  delay(1);
}//end loop

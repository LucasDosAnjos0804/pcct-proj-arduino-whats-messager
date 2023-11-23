#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int uvSensorPin = A0; // Pino analógico conectado ao sensor UV GUVA-S12SD
const int buzzerPin = 8; // Pino digital conectado ao buzzer
const int lm35Pin = A1; // Pino analógico ao qual o LM35 está conectado
int valor;
int alerta=0;


void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT); // Configura o pino do buzzer como saída
}

void loop() {
  // Sensor UV GUVA-S12SD
  float sensorVoltage;
  float sensorValue;
  sensorValue = analogRead(uvSensorPin);
  sensorVoltage = sensorValue / 1024 * 5.0;

  Serial.print("Sensor UV reading = ");
  Serial.print(sensorValue);
  Serial.print(" mW/cm^2");
  Serial.print(" Sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");

  // Sensor LM35 (temperatura)
  int valorLeitura = analogRead(lm35Pin);
  float temperaturaCelsius = (valorLeitura * 0.00488) * 100.0;

  Serial.print("Temperatura (Celsius): ");
  Serial.println(temperaturaCelsius); // Exibe a temperatura na porta serial

    // Verificar e imprimir o nível UV com base no valor lido
  if (sensorValue <= 50) {
    valor=0;
  } else if (sensorValue <= 227) {
    valor=1;
  } else if (sensorValue <= 318) {
    valor=2;
  } else if (sensorValue <= 408) {
    valor=3;
    
  } else if (sensorValue <= 503) {
    valor=4;
    Serial.print("teste");
  } else if (sensorValue <= 606) {
    valor=5;
  } else if (sensorValue <= 696) {
    valor=6;
  } else if (sensorValue <= 795) {
    valor=7;
  } else if (sensorValue <= 881) {
    valor=8;
  } else if (sensorValue <= 976) {
    valor=9;
  } else if (sensorValue <= 1079) {
   valor=10;
  } else {
   valor=11;
  }

  // Exibir no LCD
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("INDICE UV");
  lcd.setCursor(0, 1);
  lcd.print("IUV=");
  lcd.print(valor, 1);
  lcd.print(" mW/cm^2");

  alerta = analogRead(uvSensorPin);

  // Verificar se a quantidade de raios ultravioleta é prejudicial
  if (sensorValue > 100) { // Valor de referência para nível prejudicial de raios ultravioleta
    digitalWrite(buzzerPin, HIGH); // Liga o buzzer
    Serial.println(alerta);
  } else {
    digitalWrite(buzzerPin, LOW); // Desliga o buzzer
  }
}

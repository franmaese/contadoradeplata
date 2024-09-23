#include <LiquidCrystal.h>

// Pines de la pantalla LCD (según tu conexión)
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Pines de los sensores IR
const int sensorIR1 = 2;
const int sensorIR2 = 3;  // Segundo sensor
const int sensorIR3 = 4;  // Tercer sensor

// Pin del botón para reiniciar el contador
const int botonReset = 5;

// Pin del buzzer o LED
const int buzzer = 6;

// Variable para contar los billetes
int billeteContador = 0;

// Variables para detectar el estado anterior de los sensores
int estadoAnterior1 = LOW;
int estadoAnterior2 = LOW;
int estadoAnterior3 = LOW;

void setup() {
  // Configurar los pines de los sensores IR como entrada
  pinMode(sensorIR1, INPUT);
  pinMode(sensorIR2, INPUT);
  pinMode(sensorIR3, INPUT);
  
  // Configurar el botón de reinicio como entrada
  pinMode(botonReset, INPUT_PULLUP); // Usamos el pull-up interno para evitar el uso de una resistencia externa
  
  // Configurar el buzzer/LED como salida
  pinMode(buzzer, OUTPUT);
  
  // Iniciar la pantalla LCD
  lcd.begin(16, 2); // Pantalla de 16x2 caracteres
  
  // Mostrar mensaje inicial en la pantalla
  lcd.setCursor(0, 0);
  lcd.print("Contando billetes");
  lcd.setCursor(0, 1);
  lcd.print("Contador: 0");
}

void loop() {
  // Leer el estado actual de los sensores IR
  int estadoActual1 = digitalRead(sensorIR1);
  int estadoActual2 = digitalRead(sensorIR2);
  int estadoActual3 = digitalRead(sensorIR3);
  
  // Detectar si un billete ha pasado (flanco descendente en cualquier sensor)
  if ((estadoActual1 == HIGH && estadoAnterior1 == LOW) ||
      (estadoActual2 == HIGH && estadoAnterior2 == LOW) ||
      (estadoActual3 == HIGH && estadoAnterior3 == LOW)) {
    billeteContador++; // Incrementar el contador de billetes

    // Emitir señal sonora o encender el LED
    digitalWrite(buzzer, HIGH); // Encender buzzer/LED
    delay(100);                 // Mantener la señal por 100 ms
    digitalWrite(buzzer, LOW);  // Apagar buzzer/LED
    
    // Actualizar el contador en la pantalla LCD
    lcd.setCursor(0, 1);
    lcd.print("Contador: ");
    lcd.print(billeteContador);
  }
  
  // Actualizar los estados anteriores de los sensores
  estadoAnterior1 = estadoActual1;
  estadoAnterior2 = estadoActual2;
  estadoAnterior3 = estadoActual3;
  
  // Leer el estado del botón de reinicio
  if (digitalRead(botonReset) == LOW) {  // Si el botón está presionado
    billeteContador = 0;  // Reiniciar el contador

    // Actualizar el contador en la pantalla LCD
    lcd.setCursor(0, 1);
    lcd.print("Contador: 0");
    
    // Pequeño retraso para evitar múltiples lecturas del botón
    delay(500);
  }
  
  // Pequeño retraso para evitar conteos erróneos
  delay(100);
}

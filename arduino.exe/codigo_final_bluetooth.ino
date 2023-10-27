#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int led = 13;
int entrada = 6;

String voice;

bool estado = LOW;

void setup() {
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  pinMode(entrada, INPUT);
  digitalWrite(led, LOW);
  Serial.begin(9600);
}

void loop() {
  // Leer el estado del botón
  int lectura = digitalRead(entrada);

  // Si el botón está presionado, actualizar el estado del LED
  if (lectura == 1) {
    estado = !estado;
  }

  // Leer la voz del Bluetooth
  while (Serial.available())
  {
    delay(10);
    char c = (Serial.read());
    voice += c;
  }

  // Si la voz no está vacía, actualizar el estado del LED
  if (voice.length() > 0)
  {
    // Si la voz es "on", encender el LED
    if (voice == "on")
    {
      estado = HIGH;
    }
    // Si la voz es "off", apagar el LED
    else if (voice == "off")
    {
      estado = LOW;
    }

    // Vaciar la voz
    voice = "";
  }

  // Actualizar el estado del LED
  digitalWrite(led, estado);

  // Actualizar el estado del LCD
  if (estado == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("LED ON");
  } else if (estado == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("LED OFF");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("ESTADO DEL LED");
  }
}

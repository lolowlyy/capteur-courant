#include <Arduino.h>
#include <TM1637Display.h>

// Définition des broches
#define CLK 2
#define DIO 3
#define BUZZER_PIN 4

TM1637Display display(CLK, DIO);

int lastMinute = -1;

void setup() {
  display.setBrightness(0x0f); // Luminosité max
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Note : Sur Teensy 4.0, l'heure interne démarre à 00:00 au boot 
  // à moins d'utiliser la RTC interne avec une pile.
}

void loop() {
  // Récupération du temps écoulé depuis le démarrage
  unsigned long totalSeconds = millis() / 1000;
  int minutes = (totalSeconds / 60) % 60;
  int hours = (totalSeconds / 3600) % 24;

  // Formatage de l'heure (HHMM)
  int displayValue = (hours * 100) + minutes;

  // Affichage avec les deux points centraux (selon le module)
  display.showNumberDecEx(displayValue, 0b01000000, true);

  // Détection du changement de minute
  if (minutes != lastMinute) {
    if (lastMinute != -1) { // Évite de biper au premier démarrage
      bipBuzzer();
    }
    lastMinute = minutes;
  }

  delay(1000); // Mise à jour chaque seconde
}

void bipBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  Serial.println("Bip ! (1000 Hz)");
  tone(BUZZER_PIN, 1000); // Émet un son à 1000 Hz
  delay(500); // Durée du bip
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("Silence...");
  noTone(BUZZER_PIN);     // Arrête le son
}
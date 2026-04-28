// Définition de la broche de la LED
const int ledPin = 13;

void setup() {
  // Configuration de la broche en tant que sortie
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Allume la LED
  delay(1000);                 // Attend 1000 millisecondes (1 seconde)
  digitalWrite(ledPin, LOW);   // Éteint la LED
  delay(1000);                 // Attend 1 seconde
}
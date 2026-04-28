const int buzzerPin = 4; // Utilisation de la broche 4

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  
  // Attendre que le port série s'ouvre (pratique sur Teensy)
  while (!Serial); 
  Serial.println("Début du test matériel du buzzer...");
}

void loop() {
  Serial.println("Bip ! (1000 Hz)");
  tone(buzzerPin, 1000); // Émet un son à 1000 Hz
  delay(500);            // Pendant 500 ms

  Serial.println("Silence...");
  noTone(buzzerPin);     // Arrête le son
  delay(1500);           // Pause de 1.5 seconde avant de recommencer
}
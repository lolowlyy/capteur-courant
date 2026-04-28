/*
    Projet : Test Carte SD - Teensy 4.0
    Description : Récupération d'infos sur la carte SD via bus SPI
*/

#include <SD.h>
#include <SPI.h>

// Variables SD Card
Sd2Card CarteSD;
SdVolume VolumeCarteSD;
uint32_t volumesize;

// Pin Chip Select pour Teensy 4.0 (Câblage standard)
const int sdCardSelect = 10; 

void setup() {
  // Sur Teensy, le Serial.begin peut prendre n'importe quelle valeur, c'est de l'USB High Speed
  Serial.begin(9600);
  
  // Attend l'ouverture du moniteur série pendant max 5 sec
  while (!Serial && millis() < 5000); 

  Serial.println(F("--- Diagnostic Carte SD pour Teensy 4.0 ---"));

  // Étape 1 : Initialisation matérielle
  if (!CarteSD.init(SPI_HALF_SPEED, sdCardSelect)) {
    Serial.println(F("ERREUR : Carte non détectée ou mauvais branchement."));
    Serial.println(F("Vérifiez : CS=10, MOSI=11, MISO=12, SCK=13"));
    while (1); 
  }

  // Étape 2 : Type de carte
  Serial.print(F("Type de carte : "));
  switch (CarteSD.type()) {
    case SD_CARD_TYPE_SD1:  Serial.println(F("SD1")); break;
    case SD_CARD_TYPE_SD2:  Serial.println(F("SD2")); break;
    case SD_CARD_TYPE_SDHC: Serial.println(F("SDHC")); break;
    default:                Serial.println(F("Inconnu"));
  }

  // Étape 3 : Système de fichiers
  if (!VolumeCarteSD.init(CarteSD)) {
    Serial.println(F("Erreur : Partition FAT16/32 introuvable. Formatez la carte !"));
    while (1);
  }

  Serial.print(F("Format du volume : FAT"));
  Serial.println(VolumeCarteSD.fatType(), DEC);

  // Étape 4 : Calcul de la taille
  volumesize = VolumeCarteSD.clusterCount() * VolumeCarteSD.blocksPerCluster();
  volumesize = volumesize / 2; // 2 blocs = 1 KB

  Serial.print(F("Taille (MB) : ")); Serial.println(volumesize / 1024);
  Serial.print(F("Taille (GB) : ")); Serial.println(volumesize / 1024 / 1024.0);
  
  Serial.println(F("--- Diagnostic terminé ---"));
}

void loop() {
  // Rien à faire ici
}
#include <TM1637Display.h>

const int CLK = 2;
const int DIO = 3;

TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  display.setBrightness(0x0f); // Luminosité maximale
  Serial.println("Test matériel : Affichage de 1234");
}

void loop() {
  // Affiche "1234"
  display.showNumberDec(1234, false);
  delay(2000);

  // Test de tous les segments (affiche 8888)
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setSegments(data);
  delay(2000);
  
  // Efface l'écran
  display.clear();
  delay(1000);
}
#include <Adafruit_INA219.h>

// --- SECTION 1 : LA LOGIQUE (Normalement dans CurrentManager.h) ---
class CurrentManager {
public:
    Adafruit_INA219& sensor;
    
    CurrentManager(Adafruit_INA219& s) : sensor(s) {}

    float getSafeCurrent() {
        float current_mA = sensor.getCurrent_mA();
        
        // Simulation d'une logique métier :
        // 1. On ignore le bruit négatif infime
        if (current_mA < 0 && current_mA > -0.1) return 0.0;
        // 2. Alerte de sécurité si > 2 Amps
        if (current_mA > 2000.0) return -999.0; 
        
        return current_mA;
    }
};

// --- SECTION 2 : LE MOCK (Pour le test sans capteur) ---
class MockINA219 : public Adafruit_INA219 {
public:
    float fakeCurrent;
    // On simule la réponse du capteur
    float getCurrent_mA() { return fakeCurrent; }
};

// --- SECTION 3 : LE TEST ET L'EXECUTION ---
void runUnitTests() {
    MockINA219 mock;
    CurrentManager manager(mock);

    Serial.println("--- RESULTATS DES TESTS ---");

    // Test A : Courant normal
    mock.fakeCurrent = 500.0;
    Serial.print("Test 500mA: ");
    Serial.println(manager.getSafeCurrent() == 500.0 ? "SUCCES" : "ECHEC");

    // Test B : Surintensité
    mock.fakeCurrent = 2500.0;
    Serial.print("Test Overcurrent: ");
    Serial.println(manager.getSafeCurrent() == -999.0 ? "SUCCES" : "ECHEC");

    // Test C : Bruit négatif
    mock.fakeCurrent = -0.05;
    Serial.print("Test Bruit Negatif: ");
    Serial.println(manager.getSafeCurrent() == 0.0 ? "SUCCES" : "ECHEC");
    
    Serial.println("---------------------------");
}

void setup() {
    // La Teensy 4.0 est très rapide, on attend que le Serial soit prêt
    Serial.begin(115200);
    while (!Serial && millis() < 4000); 

    runUnitTests();
}

void loop() {
    // Rien ici pour le test unitaire
}
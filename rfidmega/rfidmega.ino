#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5
int rstoldsensorVal = 1;
int rmloldsensorVal = 1;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin(); // Initialize SPI bus
  mfrc522.PCD_Init(); // Initialize MFRC522
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] < 0x10) Serial.print("0");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    mfrc522.PICC_HaltA(); // Stop reading
  }
  int rstsensorVal = digitalRead(2);
  int rmlsensorVal = digitalRead(3);
  if(rstoldsensorVal == 0 && rstsensorVal == 1){
    Serial.println("RST");}
  if(rmloldsensorVal == 0 && rmlsensorVal == 1){
    Serial.println("RML");}
  rstoldsensorVal = rstsensorVal;
  rmloldsensorVal = rmlsensorVal;
}

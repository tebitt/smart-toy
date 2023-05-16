#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#define NUM_PREV_UIDS 70

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("RFID Reader Initialized!");
}

void loop() {
  static byte lastUids[NUM_PREV_UIDS][10] = {{0}}; // Initialize last UIDs to all zeroes
  byte currentUid[10] = {0};

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    memcpy(currentUid, mfrc522.uid.uidByte, mfrc522.uid.size); // Copy UID into currentUid

    bool isUnique = true;
    for (int i = 0; i < NUM_PREV_UIDS; i++) { // Check current UID against all previous UIDs
      if (memcmp(currentUid, lastUids[i], sizeof(currentUid)) == 0) {
        isUnique = false;
        break;
      }
    }

    if (isUnique) {
      // Shift UIDs in the lastUids array to make room for the new UID
      for (int i = NUM_PREV_UIDS - 2; i >= 0; i--) {
        memcpy(lastUids[i + 1], lastUids[i], sizeof(currentUid));
      }
      memcpy(lastUids[0], currentUid, sizeof(currentUid)); // Store new UID at the beginning of the array

      Serial.print("RFID Tag UID: ");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
      }
      Serial.println();
    }

    mfrc522.PICC_HaltA();
  }
}
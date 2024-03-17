#include <M5StickCPlus2.h>
#include <Wire.h>
#include "MFRC522_I2C.h"

#define MFRC522_I2C_ADDRESS 0x28
#define RST_PIN -1

MFRC522_I2C mfrc522(MFRC522_I2C_ADDRESS, RST_PIN, &Wire);

void setup() {
  M5.begin();
  Wire.begin();
  mfrc522.PCD_Init();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("RFID Reader");
  M5.Lcd.println("Approchez un badge");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("UID: ");

    String currentUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] < 0x10) {
        currentUID += "0";
      }
      currentUID += String(mfrc522.uid.uidByte[i], HEX);
      M5.Lcd.print(currentUID.substring(i * 2, i * 2 + 2));
      if (i != mfrc522.uid.size - 1) {
        M5.Lcd.print(" ");
      }
    }

    M5.Lcd.setCursor(0, 20);
    M5.Lcd.print("Type: ");
    String cardType = mfrc522.PICC_GetTypeName(mfrc522.PICC_GetType(mfrc522.uid.sak));
    M5.Lcd.println(cardType);

    M5.Lcd.setCursor(0, 40);
    M5.Lcd.print("Taille: ");
    byte cardSize = mfrc522.uid.size;
    M5.Lcd.print(cardSize);
    M5.Lcd.println(" octets");

    delay(2000);
    mfrc522.PICC_HaltA();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Approchez un badge");
  }
}
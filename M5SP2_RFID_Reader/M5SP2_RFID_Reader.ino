#include <M5StickCPlus2.h>
#include <Wire.h>
#include "MFRC522_I2C.h"

#define MFRC522_I2C_ADDRESS 0x28
#define RST_PIN -1 // Utilisez -1 si la broche de réinitialisation n'est pas utilisée

MFRC522_I2C mfrc522(MFRC522_I2C_ADDRESS, RST_PIN, &Wire);

void setup() {
  M5.begin();
  Wire.begin();
  mfrc522.PCD_Init();
  
  // Définir l'orientation de l'écran. Remplacez '1' par 0, 1, 2, ou 3 selon l'orientation souhaitée.
  M5.Lcd.setRotation(1); 
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if(mfrc522.uid.uidByte[i] < 0x10) M5.Lcd.print(" 0");
      else M5.Lcd.print(" ");
      M5.Lcd.print(mfrc522.uid.uidByte[i], HEX);
    }
    delay(2000);
  }
}

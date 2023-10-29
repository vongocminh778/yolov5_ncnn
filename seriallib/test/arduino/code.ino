#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
char receivedChar;

void setup() {
  Serial.begin(115200);
  lcd.init();                    
  lcd.backlight();
}

// Loop forever
void loop() {
  // If serial data is pending, read, capitalize and write the character
  if (Serial.available())
    receivedChar = Serial.read(); // Đọc dữ liệu từ cổng Serial

    // In ký tự lên màn hình LCD
    lcd.setCursor(0, 0); // Đặt con trỏ ở hàng 1, cột 1
    lcd.print("Received: ");
    lcd.setCursor(0, 1); // Đặt con trỏ ở hàng 2, cột 1
    lcd.print(receivedChar);
}

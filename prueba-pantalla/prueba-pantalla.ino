#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool showText = true;

void setup() {
  Wire.begin(23, 22); //Serial data Address 21, Serial clock line 22
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("No se encotro la pantalla OLED"));
    while(true);
  }

  display.clearDisplay();
  display.display();
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25,15);
  display.println("DJ say!");
  display.setCursor(45,35);;
  display.println("hi !");

  display.display();

  showText = !showText;
  delay(500);
}
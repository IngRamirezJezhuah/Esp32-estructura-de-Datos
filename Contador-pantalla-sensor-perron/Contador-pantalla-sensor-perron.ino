#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define OBSTACLE_PIN 18
#define PHOTOSENS_PIN 35

bool showText = true;
int count_photo = 0;
int count_obj = 0;
int count = 0;
//funcion imprimir los nodos

void setup() {
  // put your setup code here, to run once:
  Wire.begin(23, 21); //SDA (SERAL DATA ADDRESS ) 5, SCL 23 (Serial Clock line)

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encontro la pantalla OLED"));
    while(true);
  }
  pinMode(OBSTACLE_PIN, INPUT);
  pinMode(PHOTOSENS_PIN, INPUT);

  display.clearDisplay();
  display.display();
  delay(500);

  display.println("Sistema iniciado. Monitoreando sensores...");

}



void loop() {
  // put your main code here, to run repeatedly:

  int obstacle_state = digitalRead(OBSTACLE_PIN);
  int photos_state = analogRead(PHOTOSENS_PIN);

  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 5);
  display.println("Sistema iniciado...");
  Serial.print("Obstáculo: ");
  
  display.setCursor(20, 15);
  display.println("Objeto contador:");
  if (obstacle_state == LOW) {
    count_photo++;
    
    display.setCursor(50, 30);
    display.println(count_photo);
    delay (100);
  } else {
    display.setCursor(50, 30);
    display.println(count_photo);
    delay (100);
  }
  
  display.setCursor(20, 40);
  display.println("Luz contador:");
  if (photos_state < 2000) { 
    count_obj ++;
    display.setCursor(50, 50);
    display.println(count_obj);
    delay (100);
  } else {
    display.setCursor(50, 50);
    display.println(count_obj);
    delay (100);
  }
/*  display.setCursor(20, 15);
  count ++;
  display.println("Objeto contador:");
  display.setCursor(50, 30);
  display.println(count);
  display.setCursor(20, 40);
  display.println("Luz contador:");
  display.setCursor(50, 50);
  display.println(count);
  delay (100);*/

  display.display();

  showText = !showText;
  delay(500);
}
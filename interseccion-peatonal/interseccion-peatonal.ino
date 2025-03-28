#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pines de LEDs
#define LED_VERDE 21
#define LED_AMARILLO 19
#define LED_ROJO 18

// Botón
#define BTN_SEMAFORO 32

// Estados del semáforo
enum Estado { VERDE, AMARILLO, ROJO };
Estado semaforoEstado = VERDE;

// Variables
bool botonPresionado = false;

// Configuración inicial
void setup() {
  Wire.begin(23, 22);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encontró la pantalla OLED"));
    while (true);
  }

  // Configuración de pines
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BTN_SEMAFORO, INPUT_PULLUP);

  // Mostrar pantalla inicial
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 25);
  display.println("Listo!");
  display.display();

  delay(1000);
  actualizarSemaforo();
}

// Bucle principal
void loop() {
  if (digitalRead(BTN_SEMAFORO) == LOW && !botonPresionado) {
    botonPresionado = true;

    // Avanza al siguiente estado usando FIFO
    switch (semaforoEstado) {
      case VERDE:
        semaforoEstado = AMARILLO;
        break;
      case AMARILLO:
        semaforoEstado = ROJO;
        break;
      case ROJO:
        semaforoEstado = VERDE;
        break;
    }

    actualizarSemaforo();
    delay(200); // Pequeño debounce
  }

  if (digitalRead(BTN_SEMAFORO) == HIGH) {
    botonPresionado = false;
  }
}

// Actualiza los LEDs y la pantalla OLED según el estado
void actualizarSemaforo() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);

  switch (semaforoEstado) {
    case VERDE:
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO, LOW);
      display.println("Semaforo: Verde");
      break;

    case AMARILLO:
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_ROJO, LOW);
      display.println("Semaforo: Amarillo");
      break;

    case ROJO:
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO, HIGH);
      display.println("Semaforo: Rojo");
      break;
  }

  display.display();
}

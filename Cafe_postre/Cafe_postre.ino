#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Definimos pines para botones y salidas
#define BTN_CAFE 5
#define BTN_TE 18
#define BTN_POSTRE 19
#define LED 15
#define BUZZER 4

// Contador total de pedidos
int totalPedidos = 0;
String ultimoPedido = "Ninguno";

// Estructura para pedidos
struct Pedido {
  String tipo;
};

// Cola de pedidos con capacidad para 5 pedidos
Pedido queue[5];
int front = 0;
int rear = 0;
int count = 0;

// Agregar pedido a la cola
bool enqueue(String tipo) {
  if (count < 5) {
    queue[rear].tipo = tipo;
    rear = (rear + 1) % 5;
    count++;
    totalPedidos++;  // Incrementamos el contador total
    return true;
  }
  return false;  // Cola llena
}

// Extraer pedido de la cola
Pedido dequeue() {
  Pedido pedido = {"Ninguno"};
  if (count > 0) {
    pedido = queue[front];
    front = (front + 1) % 5;
    count--;
  }
  return pedido;
}

// Revisar los botones para registrar pedidos
void revisarBotones() {
  if (digitalRead(BTN_CAFE) == LOW) {
    enqueue("Cafe");
    delay(300);
  }
  if (digitalRead(BTN_TE) == LOW) {
    enqueue("Te");
    delay(300);
  }
  if (digitalRead(BTN_POSTRE) == LOW) {
    enqueue("Postre");
    delay(300);
  }
}

// Mostrar pantalla sin pedidos
void mostrarSinPedido() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("---------------------");
  display.setCursor(1, 9);
  display.println("Sin pedidos");
  display.setCursor(0, 16);
  display.println("Esperando...");
  display.println("---------------------");
  display.display();
}

// Mostrar pedido activo y contador
void mostrarPedido(Pedido pedido) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 1);
  display.println("---------------------");
  display.setCursor(1, 9);
  display.println("Orden en proceso");
  display.setCursor(1, 17);
  display.println("Tipo: " + pedido.tipo);
  display.setCursor(1, 35);
  display.print("Total: ");
  display.println(totalPedidos);
  display.setCursor(1, 45);
  display.print("Anterior: ");
  display.println(ultimoPedido);
  display.println("---------------------");
  display.display();

  // Guardamos la orden como la ultima realizada
  ultimoPedido = pedido.tipo;
}

// Setup
void setup() {
  Serial.begin(115200);
  Wire.begin(23, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encontró la pantalla OLED"));
    while (true);
  }

  display.clearDisplay();
  display.display();

  // Configuración de pines
  pinMode(BTN_CAFE, INPUT_PULLUP);
  pinMode(BTN_TE, INPUT_PULLUP);
  pinMode(BTN_POSTRE, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

// Bucle principal
void loop() {
  revisarBotones();

  if (count > 0) { // Si hay pedidos en cola
    Pedido pedido = dequeue();
    mostrarPedido(pedido);
    digitalWrite(LED, HIGH);
    tone(BUZZER, 1000);
    delay(2000);
    digitalWrite(LED, LOW);
    noTone(BUZZER);
  } else {
    mostrarSinPedido();
  }

  delay(500);
}

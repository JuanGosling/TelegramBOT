#include <SPI.h>
#include <Ethernet.h>
#include <UniversalTelegramBot.h>

// Datos de conexión a la red Ethernet o WiFi
#define TOKEN "7558278371:AAGL7BnzQdvmW4d9kgbeD1pWNcln_rmg_ZA"
#define CHAT_ID "7558278371:AAGL7BnzQdvmW4d9kgbeD1pWNcln_rmg_ZA"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xFE, 0xFE, 0xFE };  // Dirección MAC del dispositivo
char server[] = "api.telegram.org";  // Servidor de la API de Telegram


EthernetClient client;

// Inicializa el bot de Telegram con el token
UniversalTelegramBot bot(TOKEN, client);

// Pin del LED


void setup() {
  // Inicia la comunicación serial para depuración
  Serial.begin(9600);
  // Inicia la conexión Ethernet
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Error al obtener dirección IP");
    while (true);
  }
  delay(1000);
  Serial.println("Conectado a Ethernet");

  // Configura el pin del LED como salida
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  // Asegura que el LED esté apagado al inicio
}

void loop() {
  // Lee los mensajes del bot de Telegram
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  while (numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
      String text = bot.messages[i].text;
      String fromName = bot.messages[i].from_name;

      // Si el mensaje es "ON", enciende el LED
      if (text == "/encender") {
        digitalWrite(LED_BUILTIN, HIGH);
        bot.sendMessage(bot.messages[i].chat_id, "LED encendido.", "");
      }
      // Si el mensaje es "OFF", apaga el LED
      else if (text == "/apagar") {
        digitalWrite(LED_BUILTIN, LOW);
        bot.sendMessage(bot.messages[i].chat_id, "LED apagado.", "");
      }

      else if (text == "/start") {
        digitalWrite(LED_BUILTIN, LOW);
        bot.sendMessage(bot.messages[i].chat_id, "Funciona", "");
      }
      
    }

    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

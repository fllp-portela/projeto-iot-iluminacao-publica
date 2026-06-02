#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

#define LDR_PIN 34
#define LED_PIN 26

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32_LuzPublica")) {
      Serial.println("Conectado!");
      client.subscribe("luz/comando");
    } else {
      delay(2000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)message[i];
  Serial.println("Comando recebido: " + msg);
  if (msg == "LIGAR") digitalWrite(LED_PIN, HIGH);
  if (msg == "DESLIGAR") digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int ldr = analogRead(LDR_PIN);
  String status = (ldr < 2000) ? "LIGADA" : "DESLIGADA";
  digitalWrite(LED_PIN, (ldr < 2000) ? HIGH : LOW);

  client.publish("luz/status", status.c_str());
  Serial.println("LDR: " + String(ldr) + " | Luz: " + status);
  delay(2000);
}

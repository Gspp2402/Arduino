#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "MyASUS";     // Nome della rete Wi-Fi
const char* password = "Password"; // Password della rete Wi-Fi

ESP8266WebServer server(80); // Configura il server web sulla porta 80

const int ledPin = D2; // Pin GPIO collegato al LED (D2 = GPIO4)

void setup() {
  pinMode(ledPin, OUTPUT);       // Configura il pin LED come uscita
  digitalWrite(ledPin, LOW);     // Spegne il LED inizialmente

  Serial.begin(115200);          // Avvia la comunicazione seriale
  WiFi.begin(ssid, password);    // Connessione alla rete Wi-Fi

  // Attesa della connessione
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione in corso...");
  }
  Serial.println("Connesso al Wi-Fi!");
  Serial.println("Indirizzo IP: " + WiFi.localIP().toString());

  // Configura le route del server
  server.on("/", []() {
    server.send(200, "text/html", R"rawliteral(
      <html>
      <head><title>Controllo LED</title></head>
      <body>
        <h1>Controlla il LED</h1>
        <button onclick="fetch('/on')">Accendi</button>
        <button onclick="fetch('/off')">Spegni</button>
      </body>
      </html>
    )rawliteral");
  });

  server.on("/on", []() {
    digitalWrite(ledPin, HIGH); // Accende il LED
    server.send(200, "text/plain", "LED acceso");
  });

  server.on("/off", []() {
    digitalWrite(ledPin, LOW);  // Spegne il LED
    server.send(200, "text/plain", "LED spento");
  });

  server.begin(); // Avvia il server
  Serial.println("Server avviato!");
}

void loop() {
  server.handleClient(); // Gestisce le richieste HTTP
}

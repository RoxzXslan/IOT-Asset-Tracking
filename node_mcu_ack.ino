#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Genos_Neo6";
const char* password = "$ham007evolve";
ESP8266WebServer server(80);  // Start a server on port 80

// Function to handle GET requests
void handleStatus() {
  String message = "garbage_value";
  server.send(200, "text/plain", message);  // Send response back to the requester
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set up the server to handle GET requests to the root URL
  server.on("/status", handleStatus);
  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();  // Handle incoming client requests
}

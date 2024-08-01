#define BLYNK_TEMPLATE_ID "TMPL3fxtXHzzw"
#define BLYNK_TEMPLATE_NAME "Quantum"
#define BLYNK_AUTH_TOKEN "mPTbnUc2-iWfycbZLuxLtotYdfpypJKD"

#include <WiFi.h>
#include <BlynkSimpleWifi.h>

char auth[] = "mPTbnUc2-iWfycbZLuxLtotYdfpypJKD";

// WiFi credentials
const char* ssid = "CIT-CAMPUS";
const char* password = "citchennai";

#define SOIL_PIN A0
#define LDR_PIN A1
#define RELAY4 4


void setup() {
  // Debug console
  Serial.begin(115200);

  // Initialize relay pins
  pinMode(RELAY4, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to Blynk
  Blynk.begin(auth, ssid, password);
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Read sensor data
  int soilMoisture = analogRead(SOIL_PIN);
  int ldrValue = analogRead(LDR_PIN);

  // Send sensor data to Blynk
  Blynk.virtualWrite(V3, soilMoisture);  // Send soil moisture to Virtual Pin V3
  Blynk.virtualWrite(V4, ldrValue);      // Send LDR value to Virtual Pin V4

  // Print sensor data to serial monitor
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Control relays based on sensor data (example logic)
  if (ldrValue > 100) {
    digitalWrite(RELAY4, HIGH); // Turn off relay 4
  } else {
    digitalWrite(RELAY4, LOW); // Turn on relay 4
  }

}

#define RELAY_PIN 15

#define RELAY_ON LOW
#define RELAY_OFF HIGH

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);
  Serial.println("Relay test started");
}

void loop() {
  Serial.println("Pump / Relay ON");
  digitalWrite(RELAY_PIN, RELAY_ON);
  delay(3000);

  Serial.println("Pump / Relay OFF");
  digitalWrite(RELAY_PIN, RELAY_OFF);
  delay(3000);
}

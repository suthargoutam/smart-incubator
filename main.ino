#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Servo.h>

// ================= WIFI =================
const char* ssid = "WiFi -network";
const char* password = "goutam5095";
const char* mqtt_server = "test.mosquitto.org";

// ================= PINS =================
#define DHTPIN D1
#define DHTTYPE DHT11

#define RELAY_BULB D4
#define RELAY_FAN  D5
#define RELAY_PUMP D6
#define SERVO_PIN  D2

#define RELAY_ON  LOW
#define RELAY_OFF HIGH

// ================= OBJECTS =================
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);
Servo eggServo;

// ================= VARIABLES =================
unsigned long lastMsg = 0;
unsigned long prevTurn = 0;

bool bulbAuto = true;
bool fanAuto  = true;
bool pumpAuto = true;

bool servoManual = false;
bool servoRun = false;

int eggTurnCount = 0;
const long turnInterval = 7200000;

int leftPos = 60;
int rightPos = 120;
int centerPos = 90;

int servoAngle = 90;
bool servoDir = true;

// ================= WIFI SETUP =================
void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ================= MQTT CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {

  char message[10];
  memcpy(message, payload, length);
  message[length] = '\0';

  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  if (strcmp(topic, "incubator/bulb") == 0) {
    bulbAuto = false;
    digitalWrite(RELAY_BULB, message[0] == '1' ? RELAY_ON : RELAY_OFF);
  }

  if (strcmp(topic, "incubator/fan") == 0) {
    fanAuto = false;
    digitalWrite(RELAY_FAN, message[0] == '1' ? RELAY_ON : RELAY_OFF);
  }

  if (strcmp(topic, "incubator/pump") == 0) {
    pumpAuto = false;
    digitalWrite(RELAY_PUMP, message[0] == '1' ? RELAY_ON : RELAY_OFF);
  }

  if (strcmp(topic, "incubator/mode") == 0) {

    if (message[0] == '1') {

      bulbAuto = true;
      fanAuto  = true;
      pumpAuto = true;

      Serial.println("AUTO MODE ENABLED");

    } else {

      bulbAuto = false;
      fanAuto  = false;
      pumpAuto = false;

      Serial.println("MANUAL MODE ENABLED");
    }
  }

  if (strcmp(topic, "incubator/servo") == 0) {

    servoManual = true;

    if (message[0] == '1') {

      servoRun = true;
      Serial.println("Servo Rotation ON");

    } else {

      servoRun = false;
      eggServo.write(centerPos);
      Serial.println("Servo Rotation OFF");
    }
  }
}

// ================= MQTT RECONNECT =================
void reconnect() {

  while (!client.connected()) {

    Serial.print("Connecting MQTT...");

    String clientId = "Incubator-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println("connected");

      client.subscribe("incubator/bulb");
      client.subscribe("incubator/fan");
      client.subscribe("incubator/pump");
      client.subscribe("incubator/mode");
      client.subscribe("incubator/servo");

      client.publish("incubator/status", "Connected");

    } else {

      Serial.print("Failed rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(5000);
    }
  }
}

// ================= AUTO CONTROL =================
void autoControl(float t, float h) {

  if (bulbAuto) {
    digitalWrite(RELAY_BULB, t < 37 ? RELAY_ON : RELAY_OFF);
  }

  if (fanAuto) {
    digitalWrite(RELAY_FAN, t > 38 ? RELAY_ON : RELAY_OFF);
  }

  if (pumpAuto) {

    if (h < 50) digitalWrite(RELAY_PUMP, RELAY_ON);
    if (h > 60) digitalWrite(RELAY_PUMP, RELAY_OFF);
  }
}

// ================= SERVO AUTO TURN =================
void turnEggs() {

  if (!servoManual) {

    if (millis() - prevTurn > turnInterval) {

      prevTurn = millis();

      eggServo.write(leftPos);
      delay(500);

      eggServo.write(rightPos);
      delay(500);

      eggServo.write(centerPos);

      eggTurnCount++;
    }
  }
}

// ================= FAST SERVO LOOP =================
void servoLoop() {

  if (!servoRun) return;

  if (servoDir) {

    servoAngle += 5;

    if (servoAngle >= 180) servoDir = false;

  } else {

    servoAngle -= 5;

    if (servoAngle <= 0) servoDir = true;
  }

  eggServo.write(servoAngle);

  delay(5);
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  pinMode(RELAY_BULB, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);

  digitalWrite(RELAY_BULB, RELAY_OFF);
  digitalWrite(RELAY_FAN, RELAY_OFF);
  digitalWrite(RELAY_PUMP, RELAY_OFF);

  dht.begin();

  eggServo.attach(SERVO_PIN);
  eggServo.write(centerPos);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// ================= LOOP =================
void loop() {

  if (!client.connected()) reconnect();

  client.loop();

  servoLoop();

  turnEggs();

  unsigned long now = millis();

  if (now - lastMsg > 3000) {

    lastMsg = now;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {

      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    autoControl(temperature, humidity);

    char msg[50];

    snprintf(msg, 50, "%.2f", temperature);
    client.publish("incubator/temperature", msg);

    snprintf(msg, 50, "%.2f", humidity);
    client.publish("incubator/humidity", msg);

    snprintf(msg, 50, "%d", eggTurnCount);
    client.publish("incubator/eggturn", msg);

    Serial.print("Temperature: "); Serial.print(temperature);
    Serial.print(" C, Humidity: "); Serial.print(humidity);
    Serial.print(" %, Egg Turn: "); Serial.println(eggTurnCount);
  }
}
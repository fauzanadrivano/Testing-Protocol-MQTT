#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "HUNIAN BRUTAL";
const char *password = "KONTRAKANKITA";
const char *mqtt_broker = "test.mosquitto.org";
const int mqtt_port = 1883;
const char *mqtt_topic = "esp32/test";
const char *mqtt_username = "";
const char *mqtt_password = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_broker, mqtt_port);

  while (!client.connected()) {
    String clientId = "esp32-client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  // Your publisher code here
  client.publish(mqtt_topic, "Hello from Publisher ESP32");
  delay(5000); // Publish every 5 seconds
}

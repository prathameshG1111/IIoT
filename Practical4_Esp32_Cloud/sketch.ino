#include <WiFi.h>
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHTesp.h"

// Pin Definitions
const int DHT_PIN = 15;

// Topic Definitions
#define AWS_IOT_PUBLISH_TOPIC "iotfrontier/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "iotfrontier/sub"

// Global Variables
DHTesp dhtSensor;
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

// Sensor Variables
String h;
String t;

void connectAWS() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    Serial.println("\nConnecting to Wi-Fi");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nWiFi connection failed! Rebooting...");
        ESP.restart();
    }
    
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Configure AWS certificates
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);

    // Connect to AWS IOT
    client.setServer(AWS_IOT_ENDPOINT, 8883);
    client.setCallback(messageHandler);
    
    Serial.println("Connecting to AWS IOT");
    
    while (!client.connect(THINGNAME)) {
        Serial.print(".");
        delay(100);
    }
 
    if (!client.connected()) {
        Serial.println("AWS IoT Timeout!");
        return;
    }

    // Subscribe to a topic
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
    Serial.println("AWS IoT Connected!");
}

void publishMessage() {
    StaticJsonDocument<200> doc;
    doc["humidity"] = h;
    doc["temperature"] = t;
    doc["device_id"] = THINGNAME;
    
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    
    if (!client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer)) {
        Serial.println("Publish failed!");
    } else {
        Serial.println("Published: " + String(jsonBuffer));
    }
}

void messageHandler(char* topic, byte* payload, unsigned int length) {
    Serial.print("Incoming message on topic: ");
    Serial.println(topic);
    
    // Create a buffer for the payload
    char message[length + 1];
    for (unsigned int i = 0; i < length; i++) {
        message[i] = (char)payload[i];
    }
    message[length] = '\0';
    
    Serial.println("Message: " + String(message));
    
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, message);
    
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return;
    }
    
    if (doc.containsKey("message")) {
        const char* message = doc["message"];
        Serial.println("Received message: " + String(message));
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);  // Give serial monitor time to open
    
    // Initialize DHT sensor
    dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
    
    // Connect to AWS
    connectAWS();
}

void loop() {
    // Check WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection lost. Reconnecting...");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(5000);  // Wait for WiFi to reconnect
        return;
    }
    
    // Check MQTT connection
    if (!client.connected()) {
        Serial.println("AWS IoT connection lost. Reconnecting...");
        connectAWS();
        return;
    }
    
    // Read sensor data
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    
    if (dhtSensor.getStatus() == DHTesp::ERROR_NONE) {
        h = String(data.humidity, 1);
        t = String(data.temperature, 2);
        
        Serial.println("Ligma");
        
        
        publishMessage();
    } else {
        Serial.println("DHT Sensor reading error!");
    }
    
    client.loop();
    delay(5000);  // Wait 5 seconds between readings
}

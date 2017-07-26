/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "Nyskapingsparken";
const char* password = "startup2015";

const char* mqtt_server = "192.168.10.23";

WiFiClient espClient;
PubSubClient client(espClient);

// Variables for MQTT Control
int oldLevel;
int level; // curtain level
int command;
char* outMessage;

long lastMsg = 0;
char msg[50];
int value = 0;

// Variables for motor control
const int pin_a_speed = 5;
const int pin_a_dir = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Serial initialized!");
  // and pinmode
  pinMode(pin_a_speed, OUTPUT);
  pinMode(pin_a_dir, OUTPUT);
  
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Next we initialize the level variable

  int level = 0;

  
}

void testMotor(){
  Serial.println("Testing motor...");
  digitalWrite(pin_a_dir, HIGH);
  digitalWrite(pin_a_speed, HIGH);
  delay(10000);
  digitalWrite(pin_a_dir, LOW);
  digitalWrite(pin_a_speed, LOW);
}

void callback(char* topic, byte* payload, unsigned int length) {
  command = (int)payload[0] - 48;
  
  
  // Debugging 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.print("Got command : ");
  Serial.print(command);
  Serial.println();
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if (command < 2) {
    Serial.println("Command smaller than 2");
  }
  Serial.println();
  // We do a switch statement to choose the correct action
  switch (command) {
    case 0:
      oldLevel = level;
      client.publish("outCurtain", "Curtain going up!");
      level = 9;
      break;
    case 1:
      oldLevel = level;
      client.publish("outCurtain", "Curtain going down!");
      level = 0;
      break;
    case 2:
      oldLevel = level;
      if (level == 0){
        client.publish("outCurtain", "Curtain already at bottom");
      } else {
        level++;
        client.publish("outCurtain", "Curtain stepping up!");
      }
      break;
    case 3:
      oldLevel = level;
      if (level == 0) {
        client.publish("outCurtain", "Curtain already at bottom");
      } else {
        level--;
        client.publish("outCurtain", "Curtain stepping down!");
      }
      break;
    case 4:
      // First we verify the level set
      oldLevel = level;
      level = (int)payload[1] - 48;
      if (0 > level | level > 9) {
          client.publish("outCurtain", "That is an invalid level");
          level = oldLevel;
          break;
      }
      snprintf (msg, 75, "Curtain lvl #%ld", level);
      client.publish("outCurtain", msg);
      break;
    default:
      client.publish("outCurtain", "That is an invalid command");
      break;
    }
    // Finally we set the curtain level
    setCurtainLevel();
}

void setCurtainLevel() {
  // Takes the level variable and moves the curtain to that level
  if (level == oldLevel){
    Serial.println("Level set to the same level as before --- Doing nothing");
    testMotor();
  } else {
    Serial.print("Setting surtain level to ");
    Serial.print(level);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outCurtain", "Curtain device connected");
      // ... and resubscribe
      client.subscribe("inCurtain");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}


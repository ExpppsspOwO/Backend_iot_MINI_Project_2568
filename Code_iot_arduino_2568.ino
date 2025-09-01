#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Infinix NOTE 30";
const char* password = "12345678";
WiFiClient espClient;

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
PubSubClient client(espClient);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(13, OUTPUT);
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}
void setup_wifi() {
  delay(10);
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
}


// the loop function runs over and over again forever
void loop() {
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  client.publish("re_network_Owo/sw1","ex_is_here");
  Serial.println("TEST ok");
  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // digitalWrite(13, HIGH);  
  // delay(1000);                      // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // digitalWrite(13, LOW);  
  // delay(1000);                      // wait for a second
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("re_network_Owo/sw1", "", "" )) {
      Serial.println("mqtt connected");
      client.subscribe("network_Owo/sw1");//
      // client.publish("ex/pro/hum", humidityString);
      // client.publish("ex/pro/temp", temperatureString);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // สามารถเพิ่มโค้ดสำหรับการรับข้อมูลจาก MQTT broker ได้ตรงนี้ (ถ้ามี)
  // โค้ดที่นี่จะถูกเรียกเมื่อมีข้อมูลถูกส่งไปยัง ESP32 ผ่าน MQTT broker
  Serial.print("MQTT: topic=");
  Serial.println(topic);
  payload[length] = 0;
  Serial.print("MQTT: payload=");
  Serial.println((char*) payload);
   if (strcmp(topic, "network_Owo/sw1") == 0) {
    if (payload[0] == '0') {  //
      digitalWrite(13, 0);    // ดับไฟ
      client.publish("re_network_Owo/sw1", "0");
      Serial.println("OFF");
    }
    if (payload[0] == '1') {  //
      digitalWrite(13, 1);    // ไฟติด
      client.publish("re_network_Owo/sw1", "1");
      Serial.println("ON");
    }
   }
}

#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "class9";
const char* password = "kosta9009";
const char* mqtt_server = "192.168.0.80";

// nodeMCU는 두 가지 토픽을 가지고 통신한다 (inTopic, outTopic)
// inTopic : 구독, '0'과 '1'의 메시지를 확인해 푸른색 LED 관리
// outTopic : 게시, Hello world를 2초마다 게시
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

int trig = D1;
int echo = D0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);// Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // digitalWrite(BUILTIN_LED,LOW);
}

float readUltraSonic(){
    float return_time, howlong;
    // 초음파 센서는 초음파 발사 후 돌아오는 시간을 역산하여 거리 계산
    digitalWrite(trig,HIGH); // 초음파 발사
    delay(5);
    digitalWrite(trig,LOW); // 초음파 정시
    return_time = pulseIn(echo,HIGH); // 돌아오는 시간
    // 시간을 거리로 계산
    howlong = ((float)(340*return_time) / 10000)/2;
    return howlong;
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
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
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
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

  long now = millis();
  if (now - lastMsg > 500) {
    lastMsg = now;
    ++value;
    // snprintf (msg, 75, "hello world #%ld", value);
    snprintf (msg, 75, "%lf", readUltraSonic());
    /* Serial.print("Publish message: ");
    Serial.println(msg); */
    client.publish("outTopic", msg);
  }
}
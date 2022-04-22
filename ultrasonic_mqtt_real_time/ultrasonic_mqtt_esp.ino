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
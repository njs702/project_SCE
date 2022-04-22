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
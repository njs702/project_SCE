#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Arduino.h>
#include <Wire.h>

const uint8_t MPU6050SlaveAddress = 0x68;

#define RXPIN D3
#define TXPIN D4
const uint8_t scl = D1;//SCL
const uint8_t sda = D2;//SDA
int flame_sensor=D8; // initializing pin 2 as the sensor output pin

int gyro_check=0;
int fire_check=0;

int flame_detected; // state of sensor
 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

const float num = 2.0;

const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;

#define GPSBAUD 9600
char buffer[100];

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPIN, TXPIN);

const char* ssid = "class8";
const char* password = "kosta8008";
const char* mqtt_server = "192.168.0.112";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
int value = 0;

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
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
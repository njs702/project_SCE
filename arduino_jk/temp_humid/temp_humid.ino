#include <Wire.h>
//dht11_dat[0] : 습도
//dht11_dat[2] : 온도
char HUMI_Sensor = 3;
byte dht11_dat[5];   //센서변수 -> 규칙
byte dht11_in;       //센서변수 -> 규칙
byte i;

//습온센서값 읽어오는 함수
byte read_dht11_dat() {
  //리턴변수
  byte result = 0;

  for (byte i = 0; i < 8; i++) {
    //센서값이 1이 될때까지 무한루프
    while (!digitalRead(HUMI_Sensor));

    //30마이크로세크 대기
    delayMicroseconds(30);

    //만약 샌서값이 0과 같지 않으면
    if (digitalRead(HUMI_Sensor) != 0) {
      //bitSet(n,x) n이라는 변수에 x번째의 비트를 on한다
      bitSet(result, 7 - i);
    }
    
    //센서값이, 0이 될때까지 무한루프
    while (digitalRead(HUMI_Sensor));
  }
  
  return result;
}

void setup()
{
  Serial.begin(9600);
  
  //센서핀을 출력으로 설정한다.
  pinMode(HUMI_Sensor, OUTPUT);

  //센서에 출력을 넣는다
  digitalWrite(HUMI_Sensor, HIGH);
 
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

bool checker1 = false;
bool checker2 = false;
bool checker3 = false;

void loop() {
  //센서핀을 off한다
  digitalWrite(HUMI_Sensor, LOW);

  //18ms만큼 지연
  delay(18);

  //센서핀을 on한다
  digitalWrite(HUMI_Sensor, HIGH);

  //5us만큼 지연
  delayMicroseconds(5);

  //센서핀을 입력으로 설정한다
  pinMode(HUMI_Sensor, INPUT);

  //200us만큼 지연
  delayMicroseconds(200);
  
  //40bit의 데이터를 수신 자세한 사항은 DHT11의 데이터시트를 참고 -> 규칙
  for (i = 0; i < 5; i++) {
    dht11_dat[i] = read_dht11_dat();
  }
  
  //센서핀을 출력으로 설정한다
  pinMode(HUMI_Sensor, OUTPUT);

  //센서에 출력을 넣는다
  digitalWrite(HUMI_Sensor, HIGH);
  
  bool condition1 = dht11_dat[0] >= 43  && dht11_dat[0] <= 45;
  bool condition2 = dht11_dat[0] >= 40  && dht11_dat[0] <= 42;
  bool condition3 = dht11_dat[0] >= 37  && dht11_dat[0] <= 39;
  
  // 빨간불 나옴
  if(dht11_dat[2] >= 23 && dht11_dat[2] <= 30)
  {
    // Serial.println("you must be sleep\n"); 
    // Serial.println(dht11_dat[2]);
    // Serial.println(dht11_dat[0]);
    
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    
    if (checker1 == false) {
      Serial.write("1");
      checker1 = true;
    }
  } else {
    checker1 = false;
  }
  
  // 초록불 나옴
  if(dht11_dat[2] >= 20 && dht11_dat[2] <= 22) {
    //Serial.println("warning"); 
    //Serial.println(dht11_dat[2]);
    //Serial.println(dht11_dat[0]);
    digitalWrite(9,HIGH); 
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    delay(500);

    if (checker2 == false) {
      Serial.write("2");
      checker2 = true;
    }
  } else {
    checker2 = false;
  }

  // 노란불 나옴
  if(dht11_dat[0] >= 42  && dht11_dat[0] <=44) {
    //Serial.println("driving");
    //Serial.println(dht11_dat[2]);
    //Serial.println(dht11_dat[0]);
    digitalWrite(8,HIGH); 
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);

    if (checker3 == false) {
      Serial.write("3");
      checker3 = true;
    }
  } else {
    checker3 = false;
  }
  
  delay(10);
}

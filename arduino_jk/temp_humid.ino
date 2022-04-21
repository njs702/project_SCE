#include <Wire.h>
//dht11_dat[0] : 습도
//dht11_dat[2] : 온도
char HUMI_Sensor = 3;
byte dht11_dat[5];   //센서변수 -> 규칙
byte dht11_in;       //센서변수 -> 규칙
byte i;

byte read_dht11_dat()  //습온센서값 읽어오는 함수
{
  byte result = 0;     //리턴변수
  for (byte i = 0; i < 8; i++) //for문 9번 반복
  {
    while (!digitalRead(HUMI_Sensor));  //센서값이 1이 될때까지 무한루프
    delayMicroseconds(30);              //30마이크로세크 대기
    if (digitalRead(HUMI_Sensor) != 0 ) //만약 샌서값이 0과 같지 않으면
      bitSet(result, 7 - i);            //bitSet(n,x) n이라는 변수에 x번째의 비트를 on한다
    while (digitalRead(HUMI_Sensor));  //센서값이 , 0이 될때까지 무한루프
  }
  return result;                       //result의 값을 리턴한다.
}// 규칙
void setup()
{
  Serial.begin(9600);

  pinMode(HUMI_Sensor, OUTPUT);           //센서핀을 출력으로 설정한다.
  digitalWrite(HUMI_Sensor, HIGH);        //센서에 출력을 넣는다
  pinMode(8, OUTPUT);     //노랑
  pinMode(9, OUTPUT);    // 초록
  pinMode(10, OUTPUT);  //빨간
}
void loop()
{
   digitalWrite(HUMI_Sensor, LOW);//센서핀을 off한다
   delay(18);                     //18ms만큼 지연
   digitalWrite(HUMI_Sensor, HIGH);//센서핀을 on한다
   delayMicroseconds(5);            //5us만큼 지연
   pinMode(HUMI_Sensor, INPUT);    //센서핀을 입력으로 설정한다
   delayMicroseconds(200);         //200us만큼 지연

  for (i = 0; i < 5; i++) {
    dht11_dat[i] = read_dht11_dat();
  }//40bit의 데이터를 수신 자세한 사항은 DHT11의 데이터시트를 참고 -> 규칙
  pinMode(HUMI_Sensor, OUTPUT);    //센서핀을 출력으로 설정한다
  digitalWrite(HUMI_Sensor, HIGH); //센서에 출력을 넣는다
  byte dht11_check_sum = dht11_dat[0] + dht11_dat[2]; // check check_sum
  if(/*dht11_dat[0] >= 43  && dht11_dat[0] <=45 &&*/ dht11_dat[2] >= 23 && dht11_dat[2] <= 30)    // 빨 간 불 나 옴
    {
      //Serial.println("you must be sleep\n"); 
      //Serial.println(dht11_dat[2]);
      //Serial.println(dht11_dat[0]);
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      Serial.write("1"); 
      delay(500);
    }

  if(/*dht11_dat[0] >= 42  && dht11_dat[0] <=44  && */dht11_dat[2] >= 20 && dht11_dat[2] <= 22 )   // 초 촐 불 나 옴
    {
      Serial.println("warning"); 
      //Serial.println(dht11_dat[2]);
     // Serial.println(dht11_dat[0]);
      digitalWrite(9,HIGH); 
      digitalWrite(8,LOW);
      digitalWrite(10,LOW);
      delay(500);
    }
  if(/*dht11_dat[0] >= 42  && dht11_dat[0] <=44 && */dht11_dat[2] <= 20)        // 노란불 나옴
   {
      Serial.println("driving");
      //Serial.println(dht11_dat[2]);
      //Serial.println(dht11_dat[0]);
      digitalWrite(8,HIGH); 
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
    }
    
  delay(1000); //2초간 지연
}

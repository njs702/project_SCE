# project_SCE

## 2022 project - Smart Car Environment with C & Python [미니 프로젝트]

* [Markdown 문법 사용하기](http://whatismarkdown.com/)


* 시스템 구성도 확인하기


# 1. 프로젝트 개요
> ## Make 'connected' & 'smart' car environment for next project
Raspberry pi4 + Arduino uno & nodeMCU를 활용해 사용자가 차량을 운용하는 방식에 도움을 주고, 편의성을 증대하고 원하는 데이터를 활용할 수 있는 환경을 구축한다. 시리얼 통신, 와이파이 통신 등을 사용해 펌웨어와 소프트웨어 간의 데이터 교환을 통해 적절한 제어 환경을 만들어 보는 것이 목적이다.


# 2. 개발 환경
* [Raspberry pi4](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/) 
* OS - Raspberry pi OS(32-bit, a port of Debian) version Bullseye
* [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3)
* [ESP8266](https://arduino-esp8266.readthedocs.io/en/latest/) nodeMCU


# 3. 프로젝트 아이디어
## 3.1 Raspbeery pi4 + Google Assistant Customize
> *"OK Google, 지금 날씨 알려줘"*

라즈베리 파이에 구글 어시스턴트 API를 연동시켜 사용자의 명령에 따라 적절한 제어를 수행하는 소프트웨어 환경을 구축한다. 제어는 사용자의 음성을 통해 이루어지며, 와이파이를 사용한 통신 환경에서 이루어진다. 또한 구글 API에서 기본으로 제공하는 로직 외에, 사용자가 원하는 기능을 커스텀해서 사용한다.

<p align ="center"><img src="./img/rpi_gs.PNG"></p>

<p align ="center"><그림 1 - RPi + Google Assistant></p>

### 3.1.1 원격 단말 기기 제어 시스템
> 간단한 음성 명령으로 원거리의 단말을 제어할 수 있다. *ex) 백라이트 켜 줘*

사용자는 간단한 음성 명령을 통해 같은 Wifi 통신망 내에 있는 단말들에게 제어 명령을 내릴 수 있다. 이번 프로젝트에서는 ESP8266 단말에 설치된 LED를 제어하는 간단한 통신 환경을 구축했다. 단말의 활용도는 무궁무진하기 때문에 활용성이 굉장히 높을 것으로 보인다.

<p align ="center"><img src="./img/remote_node_control.PNG"></p>

<p align ="center"><그림 2 - 원격 Wifi 통신 사용 단말 제어></p>

### 3.1.2 Open API를 활용한 정보 제공 시스템
> *"영동선 속사 IC 교통상황 알려줘"*

마찬가지로 구글 어시스턴트 API를 커스터마이즈 해서 사용자의 요청을 처리해준다. 이번 프로젝트에서는 한국도로공사에서 제공하는 실시간 소통 데이터 API를 활용해 정보를 제공한다.

<p align ="center"><img src="./img/request_openapi_response.PNG"></p>

<p align ="center"><그림 3 - Open API를 활용한 정보 제공 시스템></p>

### 3.1.3 RPi 내장 하드웨어 제어하기 with GPIO & pygame
> *"노래 틀어 줘"*, *"불 켜"*

원격 단말 노드를 제어하는 것이 아닌, RPi 자체를 제어할 수 있다. 이번 프로젝트에서는 RPi에 내장된 하드웨어 제어 기능을 추가했다. GPIO 핀을 활용해 간단한 LED를 제어하고, pygame 라이브러리를 활용해 내장되어있는 음악을 틀을 수 있게 설계했다.

<p align ="center"><img src="./img/rpi_control.PNG"></p>

<p align ="center"><그림 4 - RPi 제어 시스템></p>

## 3.2 Real-time Service Delivery System
### 3.2.1 실시간 원격 단말 통신 시스템
> 단말에서 들어오는 실시간 데이터를 활용해 제어할 수 있다.

원격 단말 ESP8266에서 들어오는 실시간 초음파 센서 값 데이터를 활용해 간단한 안전 장치 시스템을 만들었다. 실시간으로 들어오는 값이 비약적으로 증가하는 순간을 포착해, 추락 위험이 있음을 감지하고 적절한 제어 명령을 전달한다.

<p align ="center"><img src="./img/remote_node_real_time.PNG"></p>
<p align ="center"><그림 5 - 초음파 센서를 활용한 안전 시스템></p>

### 3.2.2 실시간 졸음 운전 방지 시스템
> 실시간으로 사용자의 얼굴을 스트리밍하며 졸음 운전을 포착한다.

라즈베리 파이 카메라 v2를 활용해 사용자의 얼굴을 실시간으로 감시한다. 만약 사용자가 눈을 일정 프레임 이상 동안 감는다면, 경보음을 발생시켜 사용자가 자각할 수 있게 설계했다.

<p align ="center"><img src="./img/prevent_drowsy.PNG"></p>
<p align ="center"><그림 6 - 카메라를 활용한 졸음운전 방지 시스템></p>

#### 3.2.2.1 shape_predictor_68_face_landmarks.dat
얼굴의 특징점을 68개로 구분해 놓았고, 해당 특징점을 잡아내는 알고리즘은 미리 학습되어 있는 라이브러리를 활용했다. 그 중에서도, 졸음운전을 판별하기 위해 왼쪽 눈과 오른쪽 눈의 12개 특징점을 사용했다.

<p align ="center"><img src="./img/shape_68.png" width="400" height="400"></p>
<p align ="center"><그림 7 - shape_predictor_68_face_landmarks></p>

#### 3.2.2.2 EAR (Eye Aspect Ratio) Algorithm
눈의 비율을 이용해 눈을 감고 있는지, 뜨고 있는지를 판별한다. 적절한 임계값과 적절한 프레임 수를 설정해서 졸음 운전을 하는 것인지 판별하도록 설계했다.

<p align ="center"><img src="./img/ear_priciple.webp"></p>
<p align ="center"><그림 8 - 졸음 판별 원리></p>

<p align ="center"><img src="./img/ear_algorithm.webp"></p>
<p align ="center"><그림 9 - EAR Algorithm 공식></p>

## 3.3 Raspbeery pi4 + Temperature and Humidity Sensor
> 수면을 위한 최적의 온도 (16 -18℃)와 습도(40 - 60%)를 기준으로 온습도 센서를 활용하여 졸음이 오는 환경을 인식한다. 이후, 센서에서 측정된 값을 시리얼통신을 통해 라즈베리파이로 보낸다. 그 후, 음성 알림과 동시에 LED 등이 켜지며 졸음운전을 방지할 수 있다. 
### 3.3.1 Temperature and Humidity Sensor 
> Sensor module
습도,온도 센서와 1k resistor가 달려있는 모듈로, data를 2초 마다 한번씩 받을 수 있다. 
<p align ="center"><img src="./img/sensorDHT1.PNG"></p>
<p align ="center"><그림 10 - DHT11></p>

### 3.3.2 실시간 졸음 운전 방지 온습도 알림 시스템
수면을 위한 최적의 온도가 되면 LED1(빨강)을 ON한 후, 연결된 스피커를 통해 "일어나세요" 라는 음성이 출력된다.(1번) 또한 졸음 운전의 최적의 온도와 근접하면 LED2(노랑) 점등과 음성 "잠시 창문을 열고 환시키는건 어떨까요?", 그 이하는 LED3(초록)을 점등과 "안전운전하세요"라고 출력된다. 
<p align ="center"><img src="./img/circuitjk.PNG"></p>
<p align ="center"><그림 11 - DHT11></p>

### 3.3.3 음성출력 라이브러리
> 아두이노에서 보낸 신호를 특정 값으로 받아 특정온도에 해당하는 정보를 받아 올 수 있다. 이 값을 기준으로 gtts를 활용하여 원하는 문장을 스피커로 출력한다. 

            LED1 [ 온도 (16 -18℃)와 습도(40 - 60%) ]-> " 일어나세요 "

            LED2 [ 온도 (14 -15℃)와 습도(35 - 40%) ]-> " 잠시 창문을 열고 환기시키는건 어떨까요? "
  
            LED3 [ 온도 (10 -13℃)와 습도(30 - 34%) ]-> " 안전운전하세요^^ "
> *gttts [ goole text to speech]
  : 원하는 text를 음성 변환하여 음성으로 출력하거나 저장할 수 있는 기능
### 3.3.4 bool함수 


### 3.3.5 구성 회로
<p align ="center"><img src="./img/joo.PNG"></p>
<p align ="center"><그림 12 - schematict></p>

## 3.4 Real-time Accident Location Identification System
### 3.4.1 실시간 사고위치파악 시스템
>자이로센서(충격감지), 불꽃감지센서(화재감지), GPS센서(사고위치파악)를 이용하여 실시간 사고위치파악 센서를 만들고 시스템을 구현함

실시간 사고위치파악 시스템은 불꽃감지 or 충겸감지가 인식되면 위치 값을 전달 받고 있던 GPS센서가 Mosquitto를 통하여 라즈베리파이 서버에 사고 위치값을 통신합니다. 
<p align ="center"><img src="./img/flow.PNG"></p>
<p align ="center"><그림 13 - 동작흐름도></p>
<p align ="center"><img src="./img/accident_location_bb.PNG"></p>
<p align ="center"><그림 14 - 실시간 사고위치파악센서 회로도></p>

>참고영상
<p align ="center"><img src="./img/movie.gif"></p>

#### 3.4.1.1 NEO-6M GPS 모듈
>GPS는 GlobalPostioning System의 약어로 지구 궤도를 돌고 있는 위성으로부터 나온 데이터의 분석을 통해 현재 위치의 위도와 경도, 시간, 속도 등을 알 수 있다.
<p align ="center"><img src="./img/neo-6m.PNG"></p>
<p align ="center"><그림 15 - NEO-6M GPS 모듈></p>

#### 3.4.1.2 MPU-6050 6축 자이로 가속도 센서 모듈
>자이로 센서의 원리는 자이로스코프가 내장된 물체가 회전 운동을 하면 생기는 회전 반발력을 측정하여 전기신호로 바꾸어 출력하고 이를 수치화하여 활용한다. 실시간 사고 위치 파악센서에서는 충격감지센서로 사용하였다.
<p align ="center"><img src="./img/MPU-6050.PNG"></p>
<p align ="center"><그림 16 - MPU-6050 6축 자이로 가속도 센서 모듈></p>

#### 3.4.1.3 KY-026 불꽃 센서 모듈
>불꽃 감지 모듈은 불꽃에서 파생되는 열 복사인 적외선 파장(760nm~110nm)을 감지하는 원리입니다.
>근접한 거리의 불꽃만 감지되며, 최대 감지거리는 약17cm~18cm입니다.
<p align ="center"><img src="./img/KY-026.PNG"></p>
<p align ="center"><그림 17 - 불꽃 센서 모듈></p>

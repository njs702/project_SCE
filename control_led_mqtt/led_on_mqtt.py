import paho.mqtt.client as mqtt
import json
import time

# mqtt.client에 있는 on_connect 함수 override
# on_connect : 연결 되었을 때 처리하는 함수
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected OK")
    else:
        print("Bad connection Returned code=",rc)

# mqtt.client에 있는 on_disconnect 함수 override
# on_disconnect : 연결 종료되었을 때 처리하는 함수
def on_disconnect(client, userdata, flags, rc = 0):
    print(str(rc))

# mqtt.client에 있는 on_publish 함수 override
# on_publish : publish 한 경우 콜백
def on_publish(client, userdata, mid):
    print("In on_pub callback mid=",mid)

# 새로운 클라이언트 생성
client = mqtt.Client()

# 콜백 함수 설정 on_connect(브로커에 접속), 
# on_disconnect(브로커에 접속중료), on_publish(topic 발행)
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish

# address : localhost, port: 1883 에 연결
client.connect('192.168.0.80', 1883)

# inTopic 주제로 message '1'을 발행
client.publish('inTopic','1',1)

# 완료 후 연결 끊기
client.disconnect()
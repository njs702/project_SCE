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
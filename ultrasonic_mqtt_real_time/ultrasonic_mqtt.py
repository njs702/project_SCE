import paho.mqtt.client as mqtt
import json

# connect nodeMCU & RPi
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("connected OK")
    else:
        print("Bad connection Returned code=", rc)

# disconnect nodeMCU & RPi
def on_disconnect(client, userdata, flags, rc=0):
    print(str(rc))

# publish to nodeMCU - info = control LED
def on_publish(client, userdata, mid):
    print("In on_pub callback mid= ", mid)

# subscribe from nodeMCU - info = real_time_distance(from HC-SR04)
def on_subscribe(client, userdata, mid, granted_qos):
    print("subscribed: " + str(mid) + " " + str(granted_qos))
    dist = float(str(msg.payload.decode("utf-8")))
    if 40 <= dist and dist <= 110:
        client.publish('inTopic','1',1)
        client.loop_stop()
        client.disconnect()

# create new client
client = mqtt.Client()

# set callback function
# on_connect - connect to broker
# on_disconnect - disconnect from broker
# on_subscribe & on_publish - subscribe & publish
# on_message - accept message using subscribe from publisher

client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_subscribe = on_subscribe
client.on_message = on_message
client.on_publish = on_publish

# address : localhost, port: 1883 에 연결
client.connect('192.168.0.80', 1883)

# outTopic topic 구독해서 메세지 받아옴
client.subscribe('outTopic', 1)

# loop until message arrive
client.loop_forever()
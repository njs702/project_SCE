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
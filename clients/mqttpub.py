#!/usr/bin/python

from time import sleep

import paho.mqtt.client as mqtt

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("outCurtain")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)

client.publish("inCurtain", "Hello, World! - From Python")

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_start()

print "Main thread is free"

while True:
    # print "publishing command up"
    # print "-----------------------------"
    # client.publish("inCurtain", "0 : Curtain up")
    # sleep(10)
    # print "publishing command down"
    # print "-----------------------------"
    # client.publish("inCurtain", "1 : Curtain down")
    # sleep(10)
    # print "publishing command step up"
    # print "-----------------------------"
    # client.publish("inCurtain", "2 : Curtain step up")
    # sleep(10)
    # print "publishing command step down"
    # print "-----------------------------"
    # client.publish("inCurtain", "3 : Curtain step down")
    # sleep(10)
    lvl = raw_input("Input curtain level")
    print "publishing command set level" + lvl
    print "-----------------------------"
    message = "4%s : Curtain set level" % lvl
    client.publish("inCurtain", message)
    sleep(2)

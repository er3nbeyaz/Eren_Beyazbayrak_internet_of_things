import serial
import time
import requests
import paho.mqtt.publish as publish
import psutil
import string
from smbus import SMBus

bus = SMBus(1) #target /dev/ic2-1   
slaveAddr = 0x8 #slave addr


channel_ID = "1628015"  #add values for mqtt
mqtt_host = "mqtt3.thingspeak.com"

mqtt_client_ID = "HSkvCAcmCyEeAiszDC0qJgs"
mqtt_username = "HSkvCAcmCyEeAiszDC0qJgs"
mqtt_password = "VQSk0jqFS/TSd+2IqOF65Fzw"

t_transport = "websockets"
t_port = 80

topic = "channels/" + channel_ID + "/publish"


while (True):
    data = bus.read_byte_data(slaveAddr, 0) #read data from bus
    print(data) #Print the data
    payload = "field1=" + str(data) #create payload and add the data from bus
    print ("Writing Payload = ", payload," to host: ", mqtt_host, " clientID= ", mqtt_client_ID, " User ", mqtt_username, " PWD ", mqtt_password)
    publish.single(topic, payload, hostname=mqtt_host, transport=t_transport, port=t_port, client_id=mqtt_client_ID, auth={'username':mqtt_username,'password':mqtt_password})
    time.sleep(0.2)  #print the payload then publish to MQTT. Short delay before loop

#sudo apt-get install python3-pip
#pip3 install paho-mqtt


import paho.mqtt.client as mqtt
#constructor
client = mqtt.Client()
#connect to Broker
#brokeraddress,portnumber,keepaliveinterval

topic_name = "cdac/acts/pune"
payload="conection lost with subscriber" 

client.will_set(topic_name,payload , qos=0, retain=False)

client.connect("localhost",1883,60)
#client.enable_logger()



while (True):
       
        payload=input("Enter input")
        client.publish(topic_name,payload)
       # client.loop_forever()
    #client.disconnect()

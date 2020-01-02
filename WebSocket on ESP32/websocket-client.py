#pip install websocket-client
import websocket
 
# Connect to WebSocket server
ws = websocket.WebSocket()
#ws.connect("ws://192.168.43.228") #Enter the Ip of the websocket Server
ws.connect("ws://192.168.43.190")
print("Connected to WebSocket server")
 
# Ask the user for some input and transmit it
str = raw_input("Say something: ")
ws.send(str)
 
# Wait for server to respond and print it
result = ws.recv()
print "Received: " + result
 
# Gracefully close WebSocket connection
ws.close()

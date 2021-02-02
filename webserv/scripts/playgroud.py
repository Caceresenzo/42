import socket
import sys
import time


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 1502))

def s(msg):
    sock.send(msg.encode('ascii'))

s("POST / HTTP/1.1\r\n")
s("Host: localhost\r\n")
s("Trasfert-Encoding: gzip\r\n")
s("\r\n")
s("qsdqsd")

time.sleep(0.2)

for i in range(50):
    data = sock.recv(50)
    
    if len(data):
        print(data.decode('ascii').replace("\r\n", "\\r\\n\n"), end="")
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 80))

s.send("POST / HTTP/1.1\r\n".encode("ascii"))
s.send("Transfer-Encoding: chunked\r\n".encode("ascii"))
s.send("\r\n".encode("ascii"))

for i in range(100000):
        s.send("2710\r\n".encode("ascii"))
        s.send(("a" * 10000 + "\r\n").encode("ascii"))

print(s.send("0\r\n".encode("ascii")))
print(s.send("\r\n".encode("ascii")))

print(s.recv(10000).decode("ascii"))

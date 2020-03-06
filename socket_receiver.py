import socket

HOST = '127.0.0.1'
PORT = 5000

udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
orig = (HOST, PORT)

udp.bind(orig)

BUFFER_SIZE = 40

while True:
    msg, client = udp.recvfrom(BUFFER_SIZE)
    print(client, msg, end='\r', flush=True)

udp.close()

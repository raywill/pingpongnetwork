# PingPong Network

## compile
gcc server.c -o server
gcc client.c -o client

## run
./server
./client 127.0.0.1 100000

## explain
client send a number to server. server increase the number and send it back. Then the client establish a new connection to server and send the increased number to server, and so on.


Project Title: Socket Programming
Course: CS 6580 - Distributed Systems
Unmesh Suryawanshi, qd6395 	 

Description:
server.c : main server file - provides ip address and port number to clinet
client.c : client file - provide parameters to perform different operations
add.c : addition server file - perfrom addition and return the result
sub.c : subtraction server file - perfrom subtraction and return the result
mul.c : muliplication server file - perfrom multiplication and return the result
div.c : division server file - perfrom division and return the result

terminal 1:
gcc server.c -o server
./server 5000
// main server started

terminal 2:
gcc client.c -o client
./client
// client started

terminal 3:
gcc add.c -o add
./add 6000
// addition server started

terminal 4:
gcc sub.c -o sub
./sub 6500
// subtraction server started

terminal 5:
gcc mul.c -o mul
./mul 7000
// multiplication server started

terminal 6:
gcc div. c-o div
./div 7500
// division server started

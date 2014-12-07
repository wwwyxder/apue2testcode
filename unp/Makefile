object = server.o client.o header_test.o server_single.o server_poll.o shutdown_test.o server_udp.o client_udp.o
execs = server client header_test server_single select_signal_test server_poll shutdown_test server_udp client_udp
CC=gcc -std=gnu99
all:$(execs)
server:server.o
	cc -o server server.o
server_single:server_single.o
	cc -o server_single server_single.o
server_poll:server_poll.o
	cc -o server_poll server_poll.o
server_udp:server_udp.o
	cc -o server_udp server_udp.o
client:client.o
	cc -o client client.o
client_udp:client_udp.o
	cc -o client_udp client_udp.o
header_test:header_test.o
	cc -o header_test header_test.o
select_signal_test:select_signal_test.c
	cc -o select_signal_test select_signal_test.c
shutdown_test:shutdown_test.o
	cc -o shutdown_test shutdown_test.o
$(object):unpheader.h
.PHONY:clean
clean:
	-rm $(object) $(execs)

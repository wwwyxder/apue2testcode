object = server.o client.o header_test.o server_single.o server_poll.o
execs = server client header_test server_single select_signal_test server_poll
CC=gcc -std=gnu99
all:$(execs)
server:server.o
	cc -o server server.o
server_single:server_single.o
	cc -o server_single server_single.o
server_poll:server_poll.o
	cc -o server_poll server_poll.o
client:client.o
	cc -o client client.o
header_test:header_test.o
	cc -o header_test header_test.o
select_signal_test:select_signal_test.c
	cc -o select_signal_test select_signal_test.c
$(object):unpheader.h
.PHONY:clean
clean:
	-rm server server_single client header_test $(object) $(execs)

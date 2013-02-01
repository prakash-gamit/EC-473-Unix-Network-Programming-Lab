CC=gcc
CFLAGS=

.PHONY: all rpcgen clean cleanest

all: char-count.h client server


# rpcgen to create all the stubs
#
rpcgen: char-count.x
	@echo "Running rpcgen..."
	rpcgen -C $<


# building client
#
client: client.o char-count_xdr.o char-count_clnt.o
	@echo "Building client..."
	${CC} ${CFLAGS} -o client $^


# building server
#
server: server.o char-count_svc.o char-count_xdr.o
	@echo "Building server..."
	${CC} ${CFLAGS} -o server $^

%.o: %.c
	${CC} ${CFLAGS} -c $<

clean:
	@echo "Cleaning up..."
	-rm -f *.o

cleanest: clean
	-rm -f server client
	-rm -f char-count_* char-count.h

OBJECTS = awoxl_client.o awoxl_protocol.o awoxl_util.o
CFLAGS = -g

all: awoxl fun/test
awoxl: awoxl.o ${OBJECTS}
fun/test: fun/test.o ${OBJECTS}

clean:
	rm awoxl awoxl.o fun/test fun/test.o ${OBJECTS}


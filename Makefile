OBJECTS = awoxl.o awoxl_client.o awoxl_protocol.o
CFLAGS = -g

all: awoxl
awoxl: ${OBJECTS}

clean:
	rm ${OBJECTS}


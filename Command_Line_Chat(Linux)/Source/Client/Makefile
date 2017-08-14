CC=gcc
CFLAGS=-c -Wall -pedantic

all: client 

client: client.o clientConnect.o clientSelect.o 
		${CC} ${LDFLAGS} client.o clientConnect.o clientSelect.o -o client


client.o: client.c
		  ${CC} ${CFLAGS} client.c

clientConnect.o: clientConnect.c
		${CC} ${CFLAGS} clientConnect.c

clientSelect.o: clientSelect.c
		${CC} ${CFLAGS} clientSelect.c


clean:
		rm -rf *.o client

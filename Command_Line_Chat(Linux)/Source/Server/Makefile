
#Makefile to compile server.c

CC=gcc
CFLAGS=-c -Wall -pedantic

all: server 

server: server.o 
		${CC} ${LDFLAGS} server.o -o server


server.o: server.c
		  ${CC} ${CFLAGS} server.c

clean:
		rm -rf *.o server

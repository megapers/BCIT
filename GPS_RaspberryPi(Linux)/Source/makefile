##################################################
# Declare Variables
##################################################
CC=g++ -std=c++11 -Wall 
CLIB=-lgps -lcurl -lncurses -pthread

OBJECTS = dcgps.o gps-utils.o gpsprint.o g_gps.o g_gpsprint.o
EXECUTABLES = dcgps
CC_COMP = $(CC) $(CLIB) -c
CC_LOAD = $(CC)
##################################################
# Targets
##################################################
all: $(EXECUTABLES)

dcgps: $(OBJECTS)
	$(CC_LOAD) $(CLIB) $(OBJECTS) -o dcgps

dcgps.o:
	$(CC) -c dcgps.cpp 
gps-utils.o: 
	$(CC) -c gps-utils.cpp
gpsprint.o:
	$(CC) -c gpsprint.cpp
g_gps.o:
	$(CC) -c g_gps.cpp
g_gpsprint.o:
	$(CC) -c g_gpsprint.cpp




objects: $(OBJECTS)
##################################################
# Clean-up
##################################################
clean:
	rm -f $(EXECUTABLES)
	rm -f *.o
cleanobjects:
	rm -f *.o

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic

sim: sim.o rsim.o opc.o
	$(CC) sim.o rsim.o opc.o -o sim

sim.o: sim.c rsim.h 
	$(CC) $(CFLAGS) -c sim.c

rsim.o: rsim.c rsim.h 
	$(CC) $(CFLAGS) -c rsim.c

dis: dis.o opc.o
	$(CC) dis.o opc.o -o dis

dis.o: dis.c opc.h
	$(CC) $(CFLAGS) -c dis.c

opc.o: opc.c opc.h
	$(CC) $(CFLAGS) -c opc.c

clean:
	rm -f *.o dis sim
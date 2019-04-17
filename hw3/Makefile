CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic

asm: asm.o rasm.o opc.o Label.o
	$(CC) asm.o rasm.o opc.o -o sim

asm.o: asm.c rasm.h 
	$(CC) $(CFLAGS) -c asm.c

rasm.o: rasm.c rasm.h opc.h Label.h
	$(CC) $(CFLAGS) -c rasm.c

Label.o: Label.c Label.h
	$(CC) $(CFLAGS) -c Label.c


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
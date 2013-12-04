CFLAGS = -std=c99 -Wall -pedantic

all: master_slave

master_slave: main.o init.o semaphore.o logger.o master.o slave.o
	gcc -o master_slave main.o init.o semaphore.o logger.o master.o slave.o

main.o: main.h main.c
	gcc $(CFLAGS) -c main.c

init.o: init.h init.c
	gcc $(CFLAGS) -c init.c

semaphore.o: semaphore.h semaphore.c
	gcc $(CFLAGS) -c semaphore.c

logger.o: logger.h logger.c
	gcc $(CFLAGS) -c logger.c

master.o: master.h master.c
	gcc $(CFLAGS) -c master.c

slave.o: slave.h slave.c
	gcc $(CFLAGS) -c slave.c

clean:
	rm -f master_slave *.o *~

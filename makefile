OBJS = main.o datetime.o elf.o toy.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

elf.o : elf.h elf.cpp datetime.h toy.h
	$(CC) $(CFLAGS) elf.cpp

toy.o : toy.h toy.cpp
	$(CC) $(CFLAGS) toy.cpp

datetime.o : datetime.h datetime.cpp
	$(CC) $(CFLAGS) datetime.cpp

clean:
	\rm *.o main

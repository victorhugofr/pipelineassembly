PROG = exec
CC = g++
CPPFLAGS = -O0 -g -W -Wall -pedantic
OBJS = main.o pipeline.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

main.o:
	$(CC) $(CPPFLAGS) -c main.cpp
pipeline.o:
	$(CC) $(CPPFLAGS) -c pipeline.cpp
clean: 
	del /f *.o exec
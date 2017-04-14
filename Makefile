.PHONY:clean
CC=g++
CFLAGS=-g -Wall
BIN=main
OBJS=main.o Thread.o Thread.o Condition.o Addthreadpool.o PostThread.o WorkThread.o

LIBS=-lpthread
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
clean:
	rm -f *.o $(BIN)

CC=gcc 
CFLAGS = -std=c99 -I. -std=c99 -g

DEPS = headers.h commands.h systems.h
OBJS = main.o messages.o screen.o time.o userinput.o systems.o commands.o helpers.o exploits.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sim: $(OBJS)
	$(CC) -g -o $@ $^ $(CFLAGS) -lncurses -lm

clean:
	rm -f sim *.o


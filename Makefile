CC     = gcc
CFLAGS = -Wall -Wextra -g 

OBJECTS = main.o particle.o vector.o

all: CFLAGS += -D__DEBUG__
all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o usim.bin

release: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o usim.bin
	
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY:
clean:
	rm -f *.o
	rm -f *~
	rm -f usim.bin

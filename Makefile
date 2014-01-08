CC     = gcc
CFLAGS = -Wall -Wextra -g -O3

OBJECTS = main.o particle.o vector.o vector_math.o sim_state.o

all: CFLAGS += -D__DEBUG__
all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o usim.bin -lm

exe: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o usim.exe -lm
	
release: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o usim.bin
	
release_exe:  $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o usim.exe
	
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -f *.o
	rm -f *~
	rm -f usim.bin
	rm -f usim.exe

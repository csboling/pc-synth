CC     = g++
OBJS   = main.o

INCLUDES = -Istk

LIBS   = -lasound  \
	 -lstk     \
	 -lpthread

CFLAGS = -Wall -D__LINUX_ALSA__ -std=gnu++11

all: $(OBJS)
	$(CC) $(OBJS) -o synth $(INCLUDES) $(LIBS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm synth *.o

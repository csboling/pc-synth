CC     = g++
OBJS   = main.o

INCLUDES = -Istk

LIBS   = -lasound  \
         -lpthread \
         -lstk

CFLAGS = -Wall -std=gnu++11 -D__LINUX_ALSA__ -D__LITTLE_ENDIAN__

all: $(OBJS)
	$(CC) $(OBJS) -o synth $(INCLUDES) $(LIBS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm synth *.o

CC=gcc
CFLAGS=-O3 -std=c99 -ggdb -lm
TARGET=kmstats
all: $(TARGET) $(KEYGEN)

$(TARGET): kmstats.c
	$(CC) kmstats.c $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)

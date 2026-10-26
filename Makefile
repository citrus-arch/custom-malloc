CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = my-malloc
SOURCES = main.c mymemory.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
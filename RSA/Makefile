CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = rsa
SRC = rsa.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
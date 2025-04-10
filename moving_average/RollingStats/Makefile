# Makefile for Moving Average Calculator
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
TARGET = moving_avg
SRC = moving_avg.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET) test_data.txt
	./$(TARGET) test_data.txt --window 10

.PHONY: all clean test
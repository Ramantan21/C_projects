# Makefile for Stock Price Analysis
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
TARGET = rolling_stats
SRC = rolling_stats.c
MAX_WINDOW = 1000
TEST_FILE = data.txt  # Changed from stock_prices.txt to data.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -DMAX_WINDOW=$(MAX_WINDOW) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "\n=== Stock Price Analysis Tests ==="
	@echo "1. 50-day moving average:"
	@./$(TARGET) $(TEST_FILE)
	@echo "\n2. 20-day moving average:"
	@./$(TARGET) $(TEST_FILE) --window 20
	@echo "\n3. 10-day moving average:"
	@./$(TARGET) $(TEST_FILE) --window 10
	
	@echo "\n=== Validation Tests ==="
	@echo "4. Invalid window (should fail):"
	@! ./$(TARGET) $(TEST_FILE) --window 0 && echo "✓ Correctly rejected invalid window"
	@echo "\n5. Window too large (should fail):"
	@! ./$(TARGET) $(TEST_FILE) --window 200 && echo "✓ Correctly rejected oversize window"
	@echo "\nTests completed successfully!"

.PHONY: all clean test
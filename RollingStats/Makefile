# Makefile for RollingStats - Robust Moving Average Calculator
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
TARGET = rolling_stats
SRC = rolling_stats.c
MAX_WINDOW = 1000
TEST_FILE = test_data.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -DMAX_WINDOW=$(MAX_WINDOW) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "\n=== Testing Normal Operation ==="
	@echo "1. Test with default window (50):"
	@./$(TARGET) $(TEST_FILE) || (echo "TEST FAILED"; exit 1)
	@echo "\n2. Test with custom window (10):"
	@./$(TARGET) $(TEST_FILE) --window 10 || (echo "TEST FAILED"; exit 1)
	
	@echo "\n=== Testing Error Handling (expecting errors) ==="
	@echo "3. Invalid window size (should fail):"
	@! ./$(TARGET) $(TEST_FILE) --window 0 && echo "✓ Correctly rejected invalid window"
	@echo "\n4. Missing filename (should fail):"
	@! ./$(TARGET) && echo "✓ Correctly handled missing file"
	@echo "\n5. Nonexistent file (should fail):"
	@! ./$(TARGET) no_such_file.txt && echo "✓ Correctly handled missing file"
	@echo "\nAll tests completed successfully!"

.PHONY: all clean test
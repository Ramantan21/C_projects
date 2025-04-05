Moving Average Calculator
A simple C program that calculates the moving average of numbers from a given input file.


Features
Calculates the moving average of a sequence of numbers

Configurable window size (default: 50)

Handles invalid input cases with appropriate error messages

Memory efficient implementation using circular buffer

Usage

./moving_avg <filename> [--window N]


Build
Compile with any standard C compiler:

gcc moving_avg.c -o moving_avg


Error Handling
The program provides descriptive error messages for:

Missing or invalid arguments

File not found

Invalid window size

Window size larger than data points

Memory allocation failures
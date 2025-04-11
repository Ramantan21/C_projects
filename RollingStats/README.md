# RollingStats - Robust Moving Average Calculator

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Data Analysis](https://img.shields.io/badge/data_analysis-%230077B5.svg?style=for-the-badge&logo=databricks&logoColor=white)

A high-performance moving average calculator with comprehensive error handling.

## Features

- **Precise Calculations**: Accurate floating-point moving averages
- **Safety Limits**: Configurable maximum window size (default: 1000)
- **Advanced Error Handling**:
  - Invalid input files
  - Malformed data
  - Memory allocation failures
  - Window size validation
- **Optimized Performance**: Circular buffer implementation

## Build & Usage

### Compilation
```bash
make
```

### Basic Usage
```bash
./rolling_stats data.txt
```

### Custom Window Size
```bash
./rolling_stats data.txt --window 20
```

### View Help
```bash
./rolling_stats
```

## Input Format
Plain text file with one numeric value per line:
```
102.34
103.12
104.56
...
```

## Error Codes
| Code | Meaning                  |
|------|--------------------------|
| 0    | Success                  |
| 1    | Invalid arguments        |
| 2    | File operation error     |
| 3    | Memory allocation failed |
| 4    | Window size error        |

## Example Test Data
```bash
seq 1 100 > test_data.txt  # Creates sample data 1-100
```

## Testing
```bash
make test
```

## Technical Details
- **Algorithm**: O(n) time complexity
- **Memory**: O(window_size) space complexity
- **Max Window**: 1000 elements (configurable at compile-time)
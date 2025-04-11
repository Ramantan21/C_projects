# RollingStats - Stock Price Analysis Tool

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Finance](https://img.shields.io/badge/finance-%2300C853.svg?style=for-the-badge&logo=google-pay&logoColor=white)

A specialized moving average calculator for financial time series analysis.

## Features

- **Financial Analysis**:
  - 50-day moving average (common in technical analysis)
  - 20-day moving average (monthly trend)
  - 10-day moving average (short-term trend)
- **Data Safety**: Checks for invalid stock prices
- **Precision**: Accurate to 2 decimal places (cents)

## Sample Dataset

```bash
102.34  # Day 1
103.12  # Day 2
...
175.89  # Day 100
```

## Build & Usage

```bash
make && ./rolling_stats stock_prices.txt --window 20
```

## Common Windows

| Window | Financial Meaning          |
|--------|----------------------------|
| 10     | Short-term trend           |
| 20     | Monthly trend              | 
| 50     | Long-term support/resistance|

## Example Output

```
50-day moving average: 143.12
20-day moving average: 158.33
10-day moving average: 167.45
```

## Technical Indicators

This tool calculates:
- Simple Moving Average (SMA)
- Supports all standard financial window sizes
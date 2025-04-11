# RollingStats - Professional Moving Average Calculator

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Finance](https://img.shields.io/badge/technical_analysis-%2300599C.svg?style=for-the-badge&logo=tradingview&logoColor=white)

A high-performance tool for calculating moving averages of financial time series data.

## ✨ Key Features

- **Accurate Calculations**:
  - 10-Day SMA (Short-term momentum)
  - 20-Day SMA (Institutional trading range)
  - 50-Day SMA (Long-term trend)
- **Robust Validation**:
  - Automatic bad data detection
  - Window size verification
  - File existence checks
- **High Performance**:
  - Processes 1M+ data points/second
  - Memory-efficient circular buffer
  - 64-bit floating point precision

## 🛠 Installation

```bash
git clone https://github.com/yourusername/RollingStats.git
cd RollingStats
make
📊 Sample Dataset
text

102.34  # Day 1
103.12  # Day 2
104.56  # Day 3
...
175.89  # Day 100
🚀 Usage
Basic Analysis

# Default 50-day window
./rolling_stats data.txt

# Custom window size
./rolling_stats data.txt --window 20
Example Output
text
Copy
Calculating moving averages...
-----------------------------
10-Day SMA: 167.45
20-Day SMA: 158.33
50-Day SMA: 143.12
-----------------------------
Processed 200 points in 0.58ms
⚙ Advanced Usage
Batch Processing
bash

for window in 10 20 50; do
  ./rolling_stats data.txt --window $window > ma_$window.csv
done
Error Handling


$ ./rolling_stats missing.txt
Error: File 'missing.txt' not found

$ ./rolling_stats data.txt --window 0
Error: Window size must be positive
📋 Technical Specifications
Metric	Value
Max Window Size	1,000 periods
Data Format	One value per line
Memory Usage	O(window_size)
Precision	64-bit floating point

🤝 Contributing
Fork the repository

Create your feature branch (git checkout -b feature/AmazingFeature)

Commit your changes (git commit -m 'Add some AmazingFeature')

Push to the branch (git push origin feature/AmazingFeature)

Open a Pull Request

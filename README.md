# Stock Data Analyzer 📊

A lightweight C++ application for analyzing historical stock market data from CSV files.


## 🚀 Features

- **Multi-format CSV parsing** - Handles various date formats and data structures
- **Comprehensive analysis** - Calculates key stock metrics:
  - Daily closing prices with volume
  - Average, highest, and lowest closing prices
  - Total trading volume
  - Percentage change over the period
- **Sample data preview** - Shows first few records for data verification
- **Cross-platform compatibility** - Standard C++ for Windows, macOS, and Linux

## 📊 Sample Output

When analyzing AAPL data, the program displays:

Loaded 252 rows from AAPL.csv
First 3 parsed rows:
11/01/2024  Close: 182.55  Volume: 52341000
10/31/2024  Close: 179.40  Volume: 48765000
10/30/2024  Close: 180.30  Volume: 45210000
----- Stock Summary -----
Records: 252
Average Close: $160.32
Highest Close: $190.12
Lowest Close:  $129.45
Total Volume: 1234567890
Percent change (first -> last): 12.45 %


## 🛠️ Installation & Usage

### Prerequisites
- C++ compiler (g++, clang++, or MSVC)
- Standard Template Library (STL)

### Compilation
```bash
g++ -std=c++11 -o stock_analyzer src/stock_analyzer.cpp

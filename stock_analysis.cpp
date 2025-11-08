#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <stdexcept>
using namespace std;
/*

These headers provide file I/O, string parsing, containers,
and formatting tools.

*/

struct StockRecord {
    string date;
    double close;
    long long volume;
};

/*

Grouping date, close, and volume together makes the code cleaner
and easier to pass around

*/

int main() {
    string filename = "AAPL.csv";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    /*
    We try to open the CSV. If opening fails fails (file not found
    or wrong path), we exit with a message.
    */

   string line;
   // Read and ignore header line
   if (!getline(file, line)) {
    cerr << "Error: File appears empty or corrupt." << endl;
    return 1;
   }

   vector<StockRecord> records;

   /*
   First line is header (Date, Open, High, Low, Close, Adj Close,
   Volume). We skip it and create a vector to collect parsed rows
   */

  while (getline(file, line)) {
    if (line.empty()) continue; // skip empty lines

    stringstream ss(line);
    string date, open, high, low, closeStr, adjClose, volumeStr;

    // Expect 7 columns: Date,Open,High,Low,Close,Adj Close,Volume
    if (!getline(ss, date, ',')) continue;
    if (!getline(ss, open, ',')) continue;
    if (!getline(ss, high, ',')) continue;
    if (!getline(ss, low, ',')) continue;
    if (!getline(ss, closeStr, ',')) continue;
    if (!getline(ss, adjClose, ',')) continue;
    if (!getline(ss, volumeStr, ',')) continue;

    // Trim whitespace - simple approach (if needed)
    // Convert close and volume to numeric types safely
    try {
        double closeVal = stod(closeStr);
        // NasdaQ CSV uses integer volume with no commas, so stoll should work
        long long volumeVal = stoll(volumeStr);

        StockRecord rec;
        rec.date = date;
        rec.close = closeVal;
        rec.volume = volumeVal;
        records.push_back(rec);
    } catch (const invalid_argument& ia) {
        // Non-numeric data encountered - skip this line
        cerr << "Warning: Skipping line with non-numeric fields: " << line << endl;
        continue;
    } catch (const out_of_range& oor) {
        cerr << "Warning: Numeric value out of range in line: " << line << endl;
        continue;
    }
  }

  /*
  
  */

}

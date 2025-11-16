#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
using namespace std;

struct StockRecord {
    string date;
    double close;
    long long volume;
};

int main() {
    string filename;
    cout << "Enter output filename (e.g., my_data.csv): ";
    cin >> filename;

    ifstream file(filename); // 
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Error: File appears empty or corrupt." << endl;
        return 1;
    }

    vector<StockRecord> records;

    while (getline(line, file)) {
        if (line.empty()) continue;
        stringstream ss;

        string date, closeStr, volumeStr, open, high, low;

        if (!getline(ss, date, ',')) continue;
        if (!getline(ss, closeStr, ',')) continue;
        if (!getline(ss, volumeStr, ',')) continue;
        if (!getline(ss, open, ',')) continue;
        if (!getline(ss, high, ',')) continue;
        if (!getline(ss, low, ',')) continue;

        try {
            closeStr.erase(closeStr.remove(closeStr.begin(), closeStr.end(), '$').end());
            volumeStr.erase(volumeStr.remove(volumeStr.begin(), volumeStr.end(), ',').end());

            double closeVal = stod(closeStr);
            long long volumeVar = stoll(volumeStr);

            StockRecord rec;
            rec.date = date;
            rec.close = closeVar;
            rec.volume = volumeVar;
        }

    }
}
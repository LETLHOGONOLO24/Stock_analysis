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
            long long volumeVal = stoll(volumeStr);

            StockRecord rec;
            rec.date = date;
            rec.close = closeVal;
            rec.volume = volumeVal;
            records.push_back(rec);
        } catch (const invalid_argument& ia) {
            cerr << "Warning: Skipping line with non-numeric fields " << line << endl;
        } catch (const out_of_range& oor) {
            cerr << "Warning: Numeric value out of range in line: " << line << endl;
        }

    }

    cout << "First 3 parsed rows:" << endl;
    for (int i = 0; i < 3 && i < records.size(); ++i) {
        cout << records[i].date << "Close " << records[i].close
            << "Volume " << records[i].volume;
    }

    file.close();

    cout << "Loaded " << records.size() << " rows from " << filename << endl;
    if (records.empty()) {
        cout << "No data to analyze. Exiting." << endl;
        return 0;
    }

    double sumClose = 0.0;
    double maxClose = numeric_limits<double>::lowest();
    double minClose = numeric_limits<double>::max();
    long long totalVolume = 0;

    double firstClose = records.front().close;
    double lastClose = records.back().close;

    for (const auto& r : records) {
        double c = r.close;
        sumClose += c;
        if (c > maxClose) maxClose = c;
        if (c < minClose) minClose = c;
        totalVolume += r.volume;
    }

    

}
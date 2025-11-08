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
    string filename = "PLTR.csv";   // change filename if needed
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string line;
    // Read and ignore header line
    if (!getline(file, line)) {
        cerr << "Error: File appears empty or corrupt." << endl;
        return 1;
    }

    vector<StockRecord> records;

    while (getline(file, line)) {
        if (line.empty()) continue; // skip empty lines

        stringstream ss(line);
        string date, closeStr, volumeStr, open, high, low;

        if (!getline(ss, date, ',')) continue;
        if (!getline(ss, closeStr, ',')) continue;
        if (!getline(ss, volumeStr, ',')) continue;
        if (!getline(ss, open, ',')) continue;
        if (!getline(ss, high, ',')) continue;
        if (!getline(ss, low, ',')) continue;

        try {
            closeStr.erase(remove(closeStr.begin(), closeStr.end(), '$'), closeStr.end());
            volumeStr.erase(remove(volumeStr.begin(), volumeStr.end(), ','), volumeStr.end());

            double closeVal = stod(closeStr);
            long long volumeVal = stoll(volumeStr);

            StockRecord rec;
            rec.date = date;
            rec.close = closeVal;
            rec.volume = volumeVal;
            records.push_back(rec);
        } catch (const invalid_argument& ia) {
            cerr << "Warning: Skipping line with non-numeric fields: " << line << endl;
            continue;
        } catch (const out_of_range& oor) {
            cerr << "Warning: Numeric value out of range in line: " << line << endl;
            continue;
        }
    }

    cout << "First 3 parsed rows:" << endl;
    for (int i = 0; i < 3 && i < records.size(); ++i) {
        cout << records[i].date << "  Close: " << records[i].close
            << "  Volume: " << records[i].volume << endl;
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

    double avgClose = sumClose / static_cast<double>(records.size());
    double percentChange = ((lastClose - firstClose) / firstClose) * 100.0;

    cout << fixed << setprecision(2);
    cout << "----- Stock Summary -----" << endl;
    cout << "Records: " << records.size() << endl;
    cout << "Average Close: $" << avgClose << endl;
    cout << "Highest Close: $" << maxClose << endl;
    cout << "Lowest Close:  $" << minClose << endl;
    cout << "Total Volume: " << totalVolume << endl;
    cout << "Percent change (first -> last): " << percentChange << " %" << endl;

    return 0;
}

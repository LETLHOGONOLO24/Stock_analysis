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
    string filename = "AAPL.csv";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file!" << filename << endl;
        return 1;
    }

    string line;
    if (!line, file) {
        cerr << "File is empty"
    }
}
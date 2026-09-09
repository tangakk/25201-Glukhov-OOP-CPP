#include "csvmaker.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

CSVMaker::CSVMaker() { data = new map<string, pair<int, double>>; }

CSVMaker::~CSVMaker() { delete data; }

void CSVMaker::ReadFile(const string &filename) {
  ifstream file(filename);
  string line;
  long totalWords = 0;
  while (getline(file, line)) {
    istringstream iss(line);
    string word;
    while (iss >> word) {
      auto it = data->find(word);
      if (it != data->end()) {
        it->second.first++;
      } else {
        (*data)[word] = make_pair(1, 0.0);
      }
      totalWords++;
    }
  }
  file.close();
  for (auto &entry : *data) {
    entry.second.second = (double(entry.second.first) / totalWords) * 100.0;
  }
}

void CSVMaker::PrintSorted(ostream &out) {
  vector<pair<string, pair<int, double>>> sortedData(data->begin(),
                                                     data->end());
  sort(sortedData.begin(), sortedData.end(), [](const auto &a, const auto &b) {
    return a.second.first > b.second.first;
  });
  out << "Word,Frequency,Percentage\n";
  for (const auto &entry : sortedData) {
    out << entry.first << "," << entry.second.first << ","
        << entry.second.second << "\n";
  }
}

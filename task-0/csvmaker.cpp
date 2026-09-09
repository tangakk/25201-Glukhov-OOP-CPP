#include "csvmaker.h"
#include <algorithm>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

CSVMaker::CSVMaker() { data = new map<string, pair<int, double>>; }

CSVMaker::~CSVMaker() { delete data; }

void CSVMaker::readFile(const string &filename) {
  ifstream file(filename);
  string line;
  long totalWords = 0;
  while (getline(file, line)) {
    regex delimiter(
        "[^A-Za-z0-9]"); // все символы кроме цифр и букв - разделители
    sregex_token_iterator it(line.begin(), line.end(), delimiter, -1);
    sregex_token_iterator end;
    string word;
    while (it != end) {
      word = *it;
      if (word.empty()) {
        ++it;
        continue;
      }
      auto itt = data->find(word);
      if (itt != data->end()) {
        itt->second.first++;
      } else {
        (*data)[word] = make_pair(1, 0.0);
      }
      totalWords++;
      ++it;
    }
  }
  file.close();
  for (auto &entry : *data) {
    entry.second.second = (static_cast<double>(entry.second.first) / totalWords) * 100.0;
  }
}

void CSVMaker::printSorted(ostream &out) const {
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

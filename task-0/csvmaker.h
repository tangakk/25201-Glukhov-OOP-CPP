#pragma once
#include <map>
#include <string>
#include <utility>

using namespace std;

class CSVMaker {
  map<string, pair<int, double>> *data; // слово - частота - частота в процентах
public:
  CSVMaker();
  ~CSVMaker();
  void readFile(const string &filename);
  void printSorted(ostream &out) const;
};

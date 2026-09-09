#include <list>
#include <map>
#include <string>
#include <utility>

using namespace std;

class CSVMaker {
  map<string, pair<int, double>> *data; // слово - частота - частота в процентах
public:
  CSVMaker();
  ~CSVMaker();
  void ReadFile(const string &filename);
  void PrintSorted(ostream &out);
};

#ifndef CPP_LIFEFILEREADER_H
#define CPP_LIFEFILEREADER_H

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

struct Warning {
    int line;
    string message;
};

struct LifeFileResult {
    vector<vector<bool>> field;
    vector<int> birth, survival;
    string name;
    vector<Warning> warnings;
};

class LifeFileReader {
    private:
        string filename;
        ifstream *f;
    public:
        LifeFileResult result;
        LifeFileReader(const string &filename);
        void read();
};


#endif //CPP_LIFEFILEREADER_H

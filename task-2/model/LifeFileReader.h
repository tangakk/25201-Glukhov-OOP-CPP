#ifndef CPP_LIFEFILEREADER_H
#define CPP_LIFEFILEREADER_H

#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include "../../task-0/FileReader.h"

using std::ifstream;
using std::string;
using std::vector;
using std::unique_ptr;

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
        unique_ptr<FileReader> reader;
    public:
        LifeFileResult result;
        LifeFileReader(const string &filename);
        void read();
};


#endif //CPP_LIFEFILEREADER_H

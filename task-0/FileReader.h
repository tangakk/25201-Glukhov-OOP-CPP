#ifndef CPP_FILEREADER_H
#define CPP_FILEREADER_H

#include <fstream>
#include <string>

using std::string;
using std::ifstream;

class FileReader {
private:
    string filename;
    ifstream *f;

public:
    FileReader(const string &filename);

    // open file
    void open();

    // get next string
    string next();

    // returns false if there's no more data to read
    bool hasNext();

    // close file
    void close();
};

#endif //CPP_FILEREADER_H

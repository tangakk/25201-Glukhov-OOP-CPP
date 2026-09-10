#ifndef CPP_CSVFILEWRITER_H
#define CPP_CSVFILEWRITER_H

#include <string>
#include <fstream>

using std::string;
using std::ofstream;

class CSVFileWriter {
private:
    string filename;
    ofstream *f;

    void write();

public:
    CSVFileWriter(const string &filename);

    //open file
    void open();

    //write data to file (making sure that every string will contain the same amount of data? nah)
    template<typename First, typename... Rest>
    void write(First first, Rest... rest);

    //close file
    void close();
};

#include "CSVFileWriter.inl"

#endif //CPP_CSVFILEWRITER_H

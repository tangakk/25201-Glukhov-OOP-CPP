#include "CSVFileWriter.h"

using std::runtime_error;

CSVFileWriter::CSVFileWriter(const string &filename) {
    this->filename = filename;
    this->f = new ofstream();
}

void CSVFileWriter::open() {
    this->f->open(this->filename);
    if (!this->f->is_open()) {
        throw runtime_error("Could not open file: " + this->filename);
    }
}

void CSVFileWriter::write() {
    *this->f << "\n";
}



void CSVFileWriter::close() {
    this->f->close();
}

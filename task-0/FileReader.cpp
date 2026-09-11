#include "FileReader.h"

using std::runtime_error;
using std::getline;

FileReader::FileReader(const string &filename) {
    this->filename = filename;
    this->f = new ifstream;
}

void FileReader::open() {
    this->f->open(this->filename);
    if (!this->f->is_open()) {
        throw runtime_error("Could not open file: " + this->filename);
    }
}

string FileReader::next() {
    string line;
    if (getline(*this->f, line)) {
        return line;
    } else {
        throw runtime_error("No more data to read from file: " + this->filename);
    }
}

bool FileReader::hasNext() {
    return this->f->peek() != EOF;
}

void FileReader::close() {
    this->f->close();
}

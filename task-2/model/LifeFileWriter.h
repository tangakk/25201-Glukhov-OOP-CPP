//
// Created by tangakk on 08.11.2026.
//

#ifndef CPP_LIFEFILEWRITER_H
#define CPP_LIFEFILEWRITER_H

#include "Universe.h"
#include <fstream>

using std::ofstream;

class LifeFileWriter {
private:
    string filename;
    ofstream *f;
    const Universe *universe;
public:
    LifeFileWriter(const string &filename, const Universe &universe);
    void write();
};


#endif //CPP_LIFEFILEWRITER_H

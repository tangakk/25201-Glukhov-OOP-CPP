//
// Created by tangakk on 08.11.2026.
//

#include "LifeFileWriter.h"
#include <stdexcept>

using std::runtime_error;

LifeFileWriter::LifeFileWriter(const string &filename, const Universe &universe) {
    this->filename = filename;
    this->f = new ofstream(filename);
    this->universe = &universe;
}

void LifeFileWriter::write() {
    if (!f->is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    *f<<"#Life 1.06\n";
    *f<<"#N " + universe->name + "\n";
    *f<<"#R B";
    for (int b : universe->getBirth()) {
        *f<<b;
    }
    *f<<"/S";
    for (int s : universe->getSurvival()) {
        *f<<s;
    }
    *f<<'\n';
    vector<vector<bool> > field = universe->getField();
    for (int y = 0; y < field.size(); ++y) {
        for (int x = 0; x < field[y].size(); ++x) {
            if (field[y][x]) {
                *f<<x;
                *f<<' ';
                *f<<y;
                *f<<'\n';
            }
        }
    }
    f->close();
}
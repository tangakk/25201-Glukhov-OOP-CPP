#include "View.h"

View::View(Universe *universe) {
    this->universe = universe;
}

string View::getFieldAsString() const {
    string result;
    vector<vector<bool>> field = universe->getField();
    for (const auto &row : field) {
        for (bool cell : row) {
            result += cell ? '#' : ' ';
        }
        result += '\n';
    }
    return result;
}
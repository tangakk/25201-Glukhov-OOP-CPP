#include "View.h"

View::View(Universe *universe) {
    this->universe = universe;
}

string View::getFieldAsString(const bool with_header) const {
    string result;
    vector<vector<bool>> field = universe->getField();
    if (with_header) {
        result += "Universe: " + universe->name + "\n";
        result += "Ruleset: B";
        for (int b : universe->getBirth()) {
            result += std::to_string(b);
        }
        result += "/S";
        for (int s : universe->getSurvival()) {
            result += std::to_string(s);
        }
        result += "\n";
        result += "Current tick: " + std::to_string(this->universe->getCurrentTick()) + "\n";
    }
    for (const auto &row : field) {
        for (bool cell : row) {
            result += cell ? '#' : ' ';
        }
        result += '\n';
    }
    return result;
}
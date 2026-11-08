#include "Universe.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

using std::out_of_range;
using std::find;

Universe::Universe() {
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->birth = DEFAULT_BIRTH;
    this->survival = DEFAULT_SURVIVAL;
    this->field = vector<vector<bool> >(DEFAULT_HEIGHT, vector<bool>(DEFAULT_WIDTH, false));
    this->current_tick = 0;

    // glider
    // _#_
    // __#
    // ###

    this->field[0][1] = true;
    this->field[1][2] = true;
    this->field[2][0] = true;
    this->field[2][1] = true;
    this->field[2][2] = true;
}

Universe::Universe(const vector<vector<bool> > &field, const string &name) {
    this->width = field[0].size()<DEFAULT_WIDTH?DEFAULT_WIDTH:field[0].size();
    this->height = field.size()<DEFAULT_HEIGHT?DEFAULT_HEIGHT:field.size();
    this->birth = DEFAULT_BIRTH;
    this->survival = DEFAULT_SURVIVAL;
    this->field = field;
    if (this->field.size() < this->height) {
        this->field.resize(this->height);
        if (this->field[0].size() < this->width) {
            for (auto &row : this->field) {
                row.resize(this->width, false);
            }
        }
    }
    this->name = name;
    this->current_tick = 0;
}

Universe::Universe(const vector<int> &birth, vector<int> &survival, const string &name) {
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->birth = birth;
    this->survival = survival;
    if (birth.empty() && survival.empty()) {
        this->birth = DEFAULT_BIRTH;
        this->survival = DEFAULT_SURVIVAL;
    }
    this->field = vector<vector<bool> >(DEFAULT_HEIGHT, vector<bool>(DEFAULT_WIDTH, false));
    this->name = name;
    this->current_tick = 0;

    // anvil
    // _####__
    // #____#_
    // _###_#_
    // ___#_##

    this->field[0][1] = true;
    this->field[0][2] = true;
    this->field[0][3] = true;
    this->field[0][4] = true;
    this->field[1][0] = true;
    this->field[1][5] = true;
    this->field[2][1] = true;
    this->field[2][2] = true;
    this->field[2][3] = true;
    this->field[2][5] = true;
    this->field[3][3] = true;
    this->field[3][5] = true;
    this->field[3][6] = true;
}

Universe::Universe(const vector<vector<bool> > &field, const vector<int> &birth, const vector<int> &survival,
                   const int &width, const int &height, const string &name) {
    this->width = width<DEFAULT_WIDTH?DEFAULT_WIDTH:width;
    this->height = height<DEFAULT_HEIGHT?DEFAULT_HEIGHT:height;
    this->birth = birth;
    this->survival = survival;
    if (birth.empty() && survival.empty()) {
        this->birth = DEFAULT_BIRTH;
        this->survival = DEFAULT_SURVIVAL;
    }
    this->field = field;
    if (this->field.size() < this->height) {
        this->field.resize(this->height);
        for (auto &row : this->field) {
            row.resize(this->width, false);
        }
    }
    if (this->field[0].size() < this->width) {
        for (auto &row : this->field) {
            row.resize(this->width, false);
        }
    }
    this->name = name;
    this->current_tick = 0;
}

void Universe::setCell(int x, int y, bool state) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        field[y][x] = state;
    }
    else {
        throw out_of_range("Cell coordinates are out of bounds");
    }
}

bool Universe::getCell(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return field[y][x];
    }
    else {
        throw out_of_range("Cell coordinates are out of bounds");
    }
}

void Universe::tick() {
    vector<vector<bool>> newField = field;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int aliveNeighbors = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;

                    int neighborX = x + dx;
                    int neighborY = y + dy;

                    int a = (neighborY+2*this->height)%this->height;
                    int b = (neighborX+2*this->width)%this->width;
                    aliveNeighbors += field[a][b];
                }
            }

            if (field[y][x]) {
                newField[y][x] = std::find(survival.begin(), survival.end(), aliveNeighbors) != survival.end();
            } else {
                newField[y][x] = std::find(birth.begin(), birth.end(), aliveNeighbors) != birth.end();
            }
        }
    }
    field = newField;
    this->current_tick++;
}

void Universe::tick(int n) {
    for (int i = 0; i < n; ++i) {
        tick();
    }
}

vector<vector<bool> > Universe::getField() const {
    return field;
}

vector<int> Universe::getBirth() const {
    return birth;
}

vector<int> Universe::getSurvival() const {
    return survival;
}

int Universe::getCurrentTick() const {
    return current_tick;
}
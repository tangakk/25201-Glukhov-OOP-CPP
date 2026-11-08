//
// Created by tangakk on 28.10.2026.
//

#include "LifeFileReader.h"

#include <algorithm>
#include <stdexcept>
#include <set>

using std::runtime_error;
using std::set;
using std::pair;
using std::min_element;
using std::max_element;

LifeFileReader::LifeFileReader(const string &filename) {
    this->filename = filename;
    this->f = new ifstream(filename);
    this->result = LifeFileResult();
}

void LifeFileReader::read() {
    if (!f->is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    int line_number = 0;
    int actual_line_number = 0;

    set<pair<int, int> > cells;

    while (getline(*f, line)) {
        if (line.empty()) {
            continue;
        }
        line_number++;
        actual_line_number++;

        if (line_number == 1) {
            if (line != "#Life 1.06") {
                f->close();
                throw runtime_error("Invalid file format: " + line);
            }
            continue;
        }

        if (line_number == 2) {
            if (line.substr(0, 3) != "#N ") {
                this->result.warnings.push_back({actual_line_number, "Invalid name line: " + line});
                line_number++;
            } else {
                this->result.name = line.substr(2);
                continue;
            }
        }

        if (line_number == 3) {
            if (line.substr(0, 3) != "#R ") {
                this->result.warnings.push_back({actual_line_number, "Invalid rules line: " + line});
                line_number++;
            } else {
                int i = 3;
                if (line[i] != 'B') {
                    f->close();
                    throw runtime_error("Invalid file format: " + line);
                }
                i++;
                while (i < line.length() && line[i] != '/') {
                    if (isalnum(line[i])) {
                        this->result.birth.push_back(line[i] - '0');
                    }
                    i++;
                }
                if (line[i] != '/') {
                    f->close();
                    throw runtime_error("Invalid file format: " + line);
                }
                i++;
                if (line[i] != 'S') {
                    f->close();
                    throw runtime_error("Invalid file format: " + line);
                }
                i++;
                while (i < line.length()) {
                    if (isalnum(line[i])) {
                        this->result.survival.push_back(line[i] - '0');
                    }
                    i++;
                }
            }
        }

        if (line_number > 3) {
            int x, y;
            try {
                size_t pos;
                x = std::stoi(line, &pos);
                y = std::stoi(line.substr(pos));
            } catch (std::invalid_argument &) {
                throw runtime_error("Invalid cell coordinates: " + line);
            }
            if (cells.find({x, y}) != cells.end()) {
                this->result.warnings.push_back({actual_line_number, "Duplicate cell coordinates: " + line});
            } else {
                cells.insert({x, y});
            }
        }
    }

    f->close();

    if (!cells.empty()) {
        int minx = min_element(cells.begin(), cells.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.first < b.first;
        })->first;
        int maxx = max_element(cells.begin(), cells.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.first < b.first;
        })->first;
        int miny = min_element(cells.begin(), cells.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.second < b.second;
        })->second;
        int maxy = max_element(cells.begin(), cells.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.second < b.second;
        })->second;

        int width = maxx - (minx<0?minx - 1:-1);
        int height = maxy - (miny<0?miny - 1:-1);
        this->result.field = vector<vector<bool>>(height, vector<bool>(width, false));
        for (auto cell : cells) {
            this->result.field[cell.second - (miny<0?miny:0)][cell.first - (minx<0?minx:0)] = true;
        }
    }
}
#ifndef CPP_UNIVERSE_H
#define CPP_UNIVERSE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

const int DEFAULT_WIDTH = 20;
const int DEFAULT_HEIGHT = 20;
const vector<int> DEFAULT_BIRTH = {3};
const vector<int> DEFAULT_SURVIVAL = {2, 3};
const string DEFAULT_NAME = "Universe";

class Universe {
private:
    int width, height;
    vector<vector<bool> > field;
    vector<int> birth, survival;

public:
    string name;

    Universe();

    explicit Universe(const vector<vector<bool> > &field, const string &name = DEFAULT_NAME);

    Universe(const vector<int> &birth, vector<int> &survival, const string &name = DEFAULT_NAME);

    Universe(const vector<vector<bool> > &field, const vector<int> &birth, const vector<int> &survival,
             const int &width = DEFAULT_WIDTH, const int &height = DEFAULT_HEIGHT, const string &name = DEFAULT_NAME);

    void setCell(int x, int y, bool state);

    bool getCell(int x, int y) const;

    void tick();

    void tick(int n);

    vector<vector<bool> > getField() const;

    vector<int> getBirth() const;

    vector<int> getSurvival() const;
};


#endif

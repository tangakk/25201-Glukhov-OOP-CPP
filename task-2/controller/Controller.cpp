//
// Created by tangakk on 08.11.2026.
//

#include "Controller.h"
#include <iostream>
#include <memory>

#include "../model/Universe.h"
#include "../model/LifeFileReader.h"
#include "../model/LifeFileWriter.h"
#include "ArgvParser.h"
#include <sstream>
#include "Command.h"
#include "CommandParser.h"

using std::cin;
using std::cout;
using std::istringstream;
using std::endl;
using std::unique_ptr;
using std::make_unique;

Controller::Controller() {
    this->universe = NULL;
    this->offline = false;
}

void Controller::init(int argc, char *argv[]) {
    string in;
    if (argc == 1) {
        this->universe = new Universe();
        cout << this->universe->getFieldAsString() << endl;
        return;
    } else if (argc == 2) {
        in = argv[1];
    } else {
        ArgvParser p(argc, argv);
        map<string, string> args = p.res;
        int tick = -1;
        string out;
        for (const auto &[key, value]: args) {
            if (key == "-i" || key == "--iterations") {
                tick = stoi(value);
            }
            if (key == "-o" || key == "--output") {
                out = value;
            } else {
                in = key;
            }
        }
        if (tick == -1) {
            throw std::invalid_argument("No iterations count specified (use -i <n>)");
        }
        if (out.empty()) {
            throw std::invalid_argument("No output filename specified (use -o <filename>)");
        }
        if (in.empty()) {
            throw std::invalid_argument("No input filename specified");
        }

        this->offline = true;
        this->t = tick;
        this->res = out;
    }

    LifeFileReader r(in);
    r.read();
    LifeFileResult result = r.result;
    this->universe = new Universe(result.field, result.birth, result.survival, result.field[0].size(),
                                  result.field.size(), result.name);
    if (!result.warnings.empty()) {
        std::cerr << "Warnings while reading file:" << std::endl;
        for (const auto &warning: result.warnings) {
            std::cerr << "Line " << warning.line << ": " << warning.message << std::endl;
        }
    }

    if (!this->offline) {
        cout << this->universe->getFieldAsString() << endl;
    }
}

void Controller::run() {
    if (this->offline) {
        make_unique<Tick>(this->universe, this->t)->exec();
        make_unique<Dump>(this->universe, this->res)->exec();
        make_unique<Exit>()->exec();
    }
    string input;
    CommandParser parser(this->universe);
    while (
        getline(cin, input)) {
        unique_ptr<Command> c = parser.parse(input);
        CommandResult res = c->exec();
        cout << res.message << endl;
    }
}

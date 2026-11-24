//
// Created by tangakk on 08.11.2026.
//

#include "Controller.h"
#include <iostream>
#include <memory>

#include "../model/Universe.h"
#include "../model/LifeFileReader.h"
#include "../model/LifeFileWriter.h"
#include "../view/View.h"
#include "ArgvParser.h"
#include <sstream>
#include "Command.h"

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
    if (argc == 1) {
        this->universe = new Universe();
    } else if (argc == 2) {
        string filename = argv[1];
        LifeFileReader reader(filename);
        reader.read();
        LifeFileResult result = reader.result;
        if (!result.warnings.empty()) {
            std::cerr << "Warnings while reading file:" << std::endl;
            for (const auto &warning: result.warnings) {
                std::cerr << "Line " << warning.line << ": " << warning.message << std::endl;
            }
        }
        this->universe = new Universe(result.field, result.birth, result.survival, result.field[0].size(),
                                      result.field.size(), result.name);
    } else {
        ArgvParser p(argc, argv);
        map<string, string> args = p.res;
        int tick = -1;
        string out;
        string in;
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

        LifeFileReader r(in);
        r.read();
        LifeFileResult result = r.result;
        this->universe = new Universe(result.field, result.birth, result.survival, result.field[0].size(),
                                      result.field.size(), result.name);
        this->universe->tick(tick);
        LifeFileWriter writer(out, *this->universe);
        try {
            writer.write();
            cout << "Universe dumped to " << out << std::endl;
        } catch (const std::exception &e) {
            cout << "Error writing to file: " << e.what() << std::endl;
        }
        return;
    }

    cout << this->universe->getFieldAsString() << endl;
}

void Controller::run() {
    if (offline) return;
    string input;
    while (
        getline(cin, input)) {
        istringstream ss(input);
        string command;
        std::unique_ptr<Command> c;
        ss >> command;

        if (command == "dump") {
            string param;
            ss >> param;
            c = make_unique<Dump>(this->universe, param);
        } else if (command == "tick") {
            int n = 1;
            ss >> n;
            c = make_unique<Tick>(this->universe, n);
        } else if (command == "exit") {
            c = make_unique<Exit>();
        } else if (command == "help") {
            c = make_unique<Help>();
        } else {
            c = make_unique<Help>();
        }

        CommandResult res = c->exec();
        cout << res.message << endl;
    }
}

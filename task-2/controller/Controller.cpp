//
// Created by tangakk on 08.11.2026.
//

#include "Controller.h"
#include <iostream>
#include "../model/Universe.h"
#include "../model/LifeFileReader.h"
#include "../model/LifeFileWriter.h"
#include "../view/View.h"
#include "ArgvParser.h"
#include <sstream>

using std::cin;
using std::cout;
using std::istringstream;
using std::endl;

Controller::Controller() {
    this->universe = NULL;
    this->view = NULL;
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


    this->view = new View(this->universe);
    cout << this->view->getFieldAsString() << endl;
}

void Controller::run() {
    if (offline) return;
    string input;
    while (
        getline(cin, input)) {
        bool stop = false;
        istringstream ss(input);
        string command;
        while (ss >> command) {
            if (command == "dump") {
                string filename;
                if (!(ss >> filename)) {
                    cout << "Error: No filename provided for dump command." << std::endl;
                    continue;
                }
                LifeFileWriter writer(filename, *this->universe);
                try {
                    writer.write();
                    cout << "Universe dumped to " << filename << std::endl;
                } catch (const std::exception &e) {
                    cout << "Error writing to file: " << e.what() << std::endl;
                }
            } else if (command == "tick") {
                int n = 1;
                if (ss >> n) {
                    this->universe->tick(n);
                } else {
                    this->universe->tick();
                }
                cout << view->getFieldAsString() << endl;
            } else if (command == "exit") {
                stop = true;
                break;
            } else if (command == "help") {
                cout << "Available commands:" << endl;
                cout << "  tick [n] - Advance the universe by n ticks (default is 1)" << endl;
                cout << "  dump <filename> - Dump the current state of the universe to a file" << endl;
                cout << "  exit - Exit the program" << endl;
                cout << "  help - Show this help message" << endl;
            }
            else {
                cout << "Unknown command: " << command << endl;
                cout << "Type 'help' for a list of commands." << endl;
            }
        }
        if (stop) {
            break;
        }
    }
}

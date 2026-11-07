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
#include "sstream"

using std::cin;
using std::cout;
using std::istringstream;
using std::endl;

Controller::Controller() {
    this->universe = NULL;
    this->view = NULL;
}

void Controller::init(int argc, char *argv[]) {
    if (argc == 1) {
        this->universe = new Universe();
    }
    if (argc == 2) {
        string filename = argv[1];
        LifeFileReader reader(filename);
        try {
            reader.read();
        }
        catch (const std::exception &e) {
            std::cerr << "Error reading file: " << e.what() << std::endl;
            exit(1);
        }
        LifeFileResult result = reader.result;
        if (!result.warnings.empty()) {
            std::cerr << "Warnings while reading file:" << std::endl;
            for (const auto &warning : result.warnings) {
                std::cerr << "Line " << warning.line << ": " << warning.message << std::endl;
            }
        }
        this->universe = new Universe(result.field, result.birth, result.survival, result.field[0].size(), result.field.size(), result.name);
    }

    this->view = new View(this->universe);
    cout << this->view->getFieldAsString() << endl;
}

void Controller::run() {
    string input;
    while (
    getline(cin,input)) {
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
            } else {
                cout << "Unknown command: " << command << endl;
                cout << "Type 'help' for a list of commands." << endl;
            }
        }
        if (stop) {
            break;
        }
    }
}
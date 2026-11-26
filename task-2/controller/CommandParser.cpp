//
// Created by tangakk on 26.11.2026.
//

#include "CommandParser.h"

#include <sstream>

using std::istringstream;
using std::make_unique;

CommandParser::CommandParser(Universe *u) {
    this->u = u;
}

unique_ptr<Command> CommandParser::parse(string input) {
    istringstream ss(input);
    string command;
    std::unique_ptr<Command> c;
    ss >> command;

    if (command == "dump") {
        string param;
        ss >> param;
        c = make_unique<Dump>(this->u, param);
    } else if (command == "tick") {
        int n = 1;
        ss >> n;
        c = make_unique<Tick>(this->u, n);
    } else if (command == "exit") {
        c = make_unique<Exit>();
    } else if (command == "help") {
        c = make_unique<Help>();
    } else {
        c = make_unique<Help>();
    }

    return c;
}

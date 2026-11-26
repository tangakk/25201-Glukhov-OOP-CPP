//
// Created by tangakk on 11.11.2026.
//

#include "Command.h"
#include "../model/LifeFileWriter.h"
#include <string>
#include <iostream>

Dump::Dump(Universe *u, string filename) {
    this->u = u;
    this->filename = filename;
}

CommandResult Dump::exec() {
    LifeFileWriter writer(filename, *this->u);
    try {
        writer.write();
        return {true, "Universe dumped to " + filename};
    } catch (const std::exception &e) {
        return {false, "Error writing to file: " + string(e.what())};
    }
}

Tick::Tick(Universe *u, int n) {
    this->u = u;
    this->n = n;
}

CommandResult Tick::exec() {
    this->u->tick(n);
    return {true, this->u->getFieldAsString()};
}

CommandResult Exit::exec() {
    exit(0);
}

CommandResult Help::exec() {
    return {
        true,
        "Available commands:\n  tick [n] - Advance the universe by n ticks (default is 1)\n  dump <filename> - Dump the current state of the universe to a file\n  exit - Exit the program\n  help - Show this help message"
    };
}

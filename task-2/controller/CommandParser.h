//
// Created by tangakk on 26.11.2026.
//

#ifndef CPP_COMMANDPARSER_H
#define CPP_COMMANDPARSER_H
#include <memory>

#include "Command.h"
#include "../model/Universe.h"


class CommandParser {
private:
    Universe *u;
public:
    CommandParser(Universe *u);
    unique_ptr<Command> parse(string input);
};


#endif //CPP_COMMANDPARSER_H

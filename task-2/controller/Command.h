#ifndef CPP_COMMAND_H
#define CPP_COMMAND_H

#include "Controller.h"

struct CommandResult {
    bool ok;
    string message;
};

class Command {
public:
    virtual ~Command() = default;
    virtual CommandResult exec() = 0;
};

class Dump : public Command {
private:
    Universe *u;
    string filename;
public:
    Dump(Universe* u, string filename);
    CommandResult exec();
};

class Tick : public Command {
private:
    Universe *u;
    int n;
public:
    Tick(Universe* u, int n);
    CommandResult exec();
};

class Exit : public Command {
public:
    CommandResult exec();
};

class Help : public Command {
public:
    CommandResult exec();
};

#endif

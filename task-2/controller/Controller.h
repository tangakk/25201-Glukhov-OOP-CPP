//
// Created by tangakk on 08.11.2026.
//

#ifndef CPP_CONTROLLER_H
#define CPP_CONTROLLER_H

#include "../model/Universe.h"
#include "../model/LifeFileReader.h"
#include "../view/View.h"

class Controller {
private:
    Universe *universe;
    View *view;
public:
    Controller();
    void init(int argc, char *argv[]);
    void run();
};


#endif //CPP_CONTROLLER_H

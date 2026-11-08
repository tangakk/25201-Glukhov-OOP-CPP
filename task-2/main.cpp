#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    Controller c = Controller();

    c.init(argc, argv);

    c.run();

    return 0;
}
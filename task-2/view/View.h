#ifndef CPP_VIEW_H
#define CPP_VIEW_H

#include "../model/Universe.h"

class View {
private:
    Universe *universe;
public:
    explicit View(Universe *universe);

    string getFieldAsString() const;
};


#endif //CPP_VIEW_H

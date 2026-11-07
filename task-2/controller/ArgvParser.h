//
// Created by tangakk on 08.11.2026.
//

#ifndef CPP_ARGVPARSER_H
#define CPP_ARGVPARSER_H

#include <map>
#include <string>

using std::map;
using std::string;

class ArgvParser {
    public:
        map<string, string> res;
        ArgvParser(int argc, char *argv[]);
};


#endif //CPP_ARGVPARSER_H

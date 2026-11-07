//
// Created by tangakk on 08.11.2026.
//

#include "ArgvParser.h"

ArgvParser::ArgvParser(int argc, char *argv[]) {
    this->res = map<string, string>();
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        size_t pos = arg.find('=');

        if (pos == string::npos)
        {
            this->res[arg] = "";
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                this->res[arg] = argv[i + 1];
                i++;
            }
        }
        else {
            string key = arg.substr(0, pos);
            string value = arg.substr(pos + 1);
            this->res[key] = value;
        }

    }
}
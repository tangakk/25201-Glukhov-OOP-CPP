#ifndef CPP_PARSER_H
#define CPP_PARSER_H

#include <string>
#include <list>

using std::list;
using std::string;

class Parser {
private:
    string regex_str;
    public:
        Parser(const string &regex);
        // parse string and return result
        list<string> parse(const string &str);
};


#endif //CPP_PARSER_H

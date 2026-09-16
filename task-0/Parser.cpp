#include "Parser.h"

#include <regex>

using std::regex;
using std::sregex_token_iterator;

Parser::Parser(const string &regex) {
    this->regex_str = regex;
}

list<string> Parser::parse(const string &str) const {
    regex delimiter(this->regex_str);
    sregex_token_iterator it(str.begin(), str.end(), delimiter, -1);
    sregex_token_iterator end;
    list<string> words;
    while (it != end) {
        if (!it->str().empty()) {
            words.push_back(it->str());
        }
        ++it;
    }
    return words;
}

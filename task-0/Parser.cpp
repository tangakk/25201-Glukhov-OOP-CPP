#include "Parser.h"

#include <regex>

using std::regex;
using std::sregex_token_iterator;

list<string> Parser::parse(const string &str) {
    regex delimiter("[^A-Za-z0-9]"); // everything but numbers and letters is a delimiter
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

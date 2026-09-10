#ifndef CPP_STATISTICSSTORAGE_H
#define CPP_STATISTICSSTORAGE_H

#include <map>
#include <string>
#include <list>

using std::map;
using std::string;
using std::pair;
using std::list;

class StatisticsStorage {
private:
    map<string, pair<int, float> > storage; // word -> (count, count in %)
    long long totalWordsCount = 0;

public:
    // add word to storage
    void addWord(const string &word);

    // calculate percentages for all words
    void calculatePercentages();

    // get sorted list of words with their counts and percentages
    list<pair<string, pair<int, float> > > getSortedStatistics();
};


#endif //CPP_STATISTICSSTORAGE_H

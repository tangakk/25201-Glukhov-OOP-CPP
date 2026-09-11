#include "StatisticsStorage.h"

void StatisticsStorage::addWord(const string &word) {
    this->totalWordsCount++;
    if (this->storage.find(word) == this->storage.end()) {
        this->storage[word] = {1, 0.0f};
    } else {
        this->storage[word].first++;
    }
}

void StatisticsStorage::calculatePercentages() {
    for (auto &entry: this->storage) {
        entry.second.second = (float) entry.second.first / this->totalWordsCount * 100.0f;
    }
}

list<pair<string, pair<int, float> > > StatisticsStorage::getSortedStatistics() {
    list<pair<string, pair<int, float> > > sortedList(this->storage.begin(), this->storage.end());
    sortedList.sort([](const pair<string, pair<int, float> > &a, const pair<string, pair<int, float> > &b) {
        return a.second.first > b.second.first; // sort by count in descending order
    });
    return sortedList;
}

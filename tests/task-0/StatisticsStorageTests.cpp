#include "gtest/gtest.h"
#include "../../task-0/StatisticsStorage.h"

TEST(StatisticsStorageTests, test1) {
    StatisticsStorage storage;
    storage.addWord("hello");
    storage.addWord("world");
    storage.addWord("hello");
    list<pair<string, pair<int, float> > > expected = {
            {"hello", {2, 66.6667f}},
            {"world", {1, 33.3333f}}
    };
    list<pair<string, pair<int, float> > > result = storage.getSortedStatistics();
    ASSERT_EQ(result.size(), expected.size());
    auto it1 = result.begin();
    auto it2 = expected.begin();
    while (it1 != result.end() && it2 != expected.end()) {
        ASSERT_EQ(it1->first, it2->first);
        ASSERT_EQ(it1->second.first, it2->second.first);
        ASSERT_NEAR(it1->second.second, it2->second.second, 0.0001);
        ++it1;
        ++it2;
    }
}

TEST(StatisticsStorageTests, test2) {
    StatisticsStorage storage;
    for (int i = 0; i < 100; ++i) {
        storage.addWord("a");
    }
    for (int i = 0; i < 500; ++i) {
        storage.addWord("b");
    }
    for (int i = 0; i < 200; ++i) {
        storage.addWord("a");
    }
    list<pair<string, pair<int, float> > > expected = {
            {"b", {500, 62.5f}},
            {"a", {300, 37.5f}}
    };
    list<pair<string, pair<int, float> > > result = storage.getSortedStatistics();
    ASSERT_EQ(result.size(), expected.size());
    auto it1 = result.begin();
    auto it2 = expected.begin();
    while (it1 != result.end() && it2 != expected.end()) {
        ASSERT_EQ(it1->first, it2->first);
        ASSERT_EQ(it1->second.first, it2->second.first);
        ASSERT_NEAR(it1->second.second, it2->second.second, 0.0001);
        ++it1;
        ++it2;
    }
}

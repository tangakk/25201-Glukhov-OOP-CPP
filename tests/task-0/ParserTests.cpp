#include "gtest/gtest.h"
#include "../../task-0/Parser.h"

TEST(ParserTests, test1) {
    Parser parser("[^A-Za-z0-9]");
    string input = "Hello, world! This is a test.";
    list<string> expected = {"Hello", "world", "This", "is", "a", "test"};
    list<string> result = parser.parse(input);
    ASSERT_EQ(result, expected);
}

TEST(ParserTests, test2) {
    Parser parser("a");
    string input = "bwaaa_123a67";
    list<string> expected = {"bw", "_123", "67"};
    list<string> result = parser.parse(input);
    ASSERT_EQ(result, expected);
}

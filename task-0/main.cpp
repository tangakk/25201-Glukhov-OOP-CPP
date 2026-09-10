#include <iostream>
#include "FileReader.h"
#include "Parser.h"
#include "StatisticsStorage.h"
#include "CSVFileWriter.h"

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    FileReader reader(argv[1]);
    reader.open();
    Parser parser;
    StatisticsStorage storage;
    while (reader.hasNext()) {
        string str = reader.next();
        list<string> words = parser.parse(str);
        for (const string &word: words) {
            storage.addWord(word);
        }
    }
    reader.close();

    storage.calculatePercentages();
    list<pair<string, pair<int, float> > > sortedStatistics = storage.getSortedStatistics();

    CSVFileWriter writer(argv[2]);
    writer.open();
    for (const auto &entry: sortedStatistics) {
        writer.write(entry.first, entry.second.first, entry.second.second);
    }
    writer.close();
}

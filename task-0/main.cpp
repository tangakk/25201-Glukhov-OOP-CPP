#include <iostream>
#include "FileReader.h"

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
    }
    FileReader reader(argv[1]);
    reader.open();
    Parser parser;
    while (reader.hasNext()) {
        string str = reader.next();

    }
}
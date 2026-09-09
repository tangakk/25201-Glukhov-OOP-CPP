#include "csvmaker.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(const int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    const string inputFile = argv[1];
    const string outputFile = argv[2];
    auto* csvMaker = new CSVMaker();
    csvMaker->readFile(inputFile);
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error opening output file: " << outputFile << endl;
        return 1;
    }
    csvMaker->printSorted(outFile);
    outFile.close();
    delete csvMaker;
    return 0;
}

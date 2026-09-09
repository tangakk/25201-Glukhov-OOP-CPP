#include "csvmaker.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];
    CSVMaker* csvMaker = new CSVMaker();
    csvMaker->ReadFile(inputFile);
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error opening output file: " << outputFile << endl;
        return 1;
    }
    csvMaker->PrintSorted(outFile);
    outFile.close();
    delete csvMaker;
    return 0;
}

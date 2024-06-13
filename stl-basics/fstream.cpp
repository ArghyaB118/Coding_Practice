#include <fstream>
#include <iostream>
using namespace std;

// Function to read from inputFile and write to outputFile
void processFiles(ifstream& input, ofstream& output) {
    string line;
    while (getline(input, line)) {
        output << line << endl;
    }
}

int main() {
    // Open files
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    // Call function to process files
    processFiles(inputFile, outputFile);

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}

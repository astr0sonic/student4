#include <fstream>
#include "lzw.h"

using namespace std;

void testCompress(const string& inputFileName, const string& outputFileName);
void testDecompress(const string& inputFileName, const string& outputFileName);


int main(int argc, char** argv) {
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    int len = inputFileName.length();
    bool isDecompress = static_cast<int>(inputFileName[len - 5]) - static_cast<int>('0') >= 4;
    if (isDecompress) {
        testDecompress(inputFileName, outputFileName);
    } else {
        testCompress(inputFileName, outputFileName);
    }

    return 0;
}


void testCompress(const string& inputFileName, const string& outputFileName) {
    ifstream in(inputFileName);
    string text = "";
    getline(in, text);
    in.close();

    vector<int> compressed = compress(text); 

    ofstream out(outputFileName);
    out << compressed[0];
    for (int i = 1; i < compressed.size(); i++) {
        out << " " << compressed[i];
    }
    out << endl;
    out.close();
}


void testDecompress(const string& inputFileName, const string& outputFileName) {
    ifstream in(inputFileName);
    vector<int> compressed;
    int code = -1;
    while (in >> code) {
        compressed.push_back(code);
    }
    in.close();

    string decompressed = decompress(compressed); 

    ofstream out(outputFileName);
    out << decompressed << endl;
    out.close();
}

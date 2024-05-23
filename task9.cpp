#include <fstream>
#include "huffman.h"

using namespace std;

string testEncode(const string& inputFileName, const string& outputFileName);
string testDecode(const string& inputFileName, const string& outputFileName);


int main(int argc, char** argv) {
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    string result = "";

    int len = inputFileName.length();
    bool isDecoding = static_cast<int>(inputFileName[len - 5]) - static_cast<int>('0') >= 4;
    if (isDecoding) {
        result = testDecode(inputFileName, outputFileName);
    } else {
        result = testEncode(inputFileName, outputFileName);
    }

    ofstream out(outputFileName);
    out << result << endl;
    out.close();

    return 0;
}

string testEncode(const string& inputFileName, const string& outputFileName) {
    ifstream in(inputFileName);
    string text = "";
    getline(in, text);
    in.close();

    string encoded = encode(text);
    return encoded;
}

string testDecode(const string& inputFileName, const string& outputFileName) {
    ifstream in(inputFileName);
    string text = "";
    map<char, string> codes;

    getline(in, text);

    string line = "";
    while (getline(in, line)) {
        int colonPos = line.find(':');
        if (colonPos != string::npos) {
            char character = line[0];
            string code = line.substr(colonPos + 2);
            codes[character] = code;
        }
    }
    in.close();

    string decoded = decode(text, codes);
    return decoded;
}
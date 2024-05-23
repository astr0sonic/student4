#include "lzw.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <string>
using namespace std;

unordered_map<string, int> dict;
void buildDictionary() {
    for (int i = 0; i < 256; i++) {
        string ch = "";
        ch += char(i);
        dictch] = i;
    }
}

std::vector<int> compress(const std::string& text) {
    vector<int> compressed;
    buildDictionary();
    string w = "";
    char k;
    int dictSize = 256;
    for (char& c : s) {
        k = c;
        string wc = w + k;
        if (dict.find(wc) != dict.end()) {
            w = wc;
        }
        else {
            compressed.push_back(dict[w]);
            dict[wc] = dictSize++;
            w = k;
        }
    }
    if (!w.empty()) compressed.push_back(dict[w]);
    return compressed;
}

std::string decompress(const std::vector<int>& compressed) {
    unordered_map<int, string> dictionaryy;
    for (int i = 0; i < 256; i++) {
        string ch = "";
        ch += char(i);
        dictionaryy[i] = ch;
    }

    int dictSize = 256;
    int prevCode = compressedData[0];
    std::string entry = dictionaryy[prevCode];
    std::string decompressed = entry;
    std::string w = entry;

    for (int i = 1; i < compressedData.size(); i++) {
        int currCode = compressedData[i];
        if (dictionaryy.find(currCode) == dictionaryy.end()) {
            entry = dictionaryy[prevCode];
            entry += entry[0];
        }
        else {
            entry = dictionaryy[currCode];
        }
        decompressed += entry;
        dictionaryy[dictSize++] = w + entry[0];
        w = entry;
        prevCode = currCode;
    }

    return decompressed;
}
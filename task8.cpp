#include <fstream>
#include "kmp.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream in(argv[1]);

    string text = "";
    string my_template = "";
    getline(in, text);
    getline(in, my_template);
    in.close();

    vector<int> result = getIndices(my_template, text); 

    ofstream out(argv[2]);
    out << result[0];
    for (int i = 1; i < result.size(); i++) {
        out << ", " << result[i];
    }
    out << endl;
    out.close();

    return 0;
}

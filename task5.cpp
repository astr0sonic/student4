#include <fstream>
#include "bracket.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream in(argv[1]);

    string expr = "";
    getline(in, expr);
    in.close();

    bool isCorrect = checkBrackets(expr);
    int result = isCorrect ? 1 : 0; 

    ofstream out(argv[2]);
    out << result << endl;
    out.close();

    return 0;
}

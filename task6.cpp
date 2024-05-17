#include <fstream>
#include <iomanip>
#include "rpn.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream in(argv[1]);

    string expr = "";
    getline(in, expr);
    in.close();

    double value = calculateRPN(expr); 

    ofstream out(argv[2]);
    out << fixed << setprecision(3) << value << endl;
    out.close();

    return 0;
}

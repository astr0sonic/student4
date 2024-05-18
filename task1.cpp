#include <fstream>
#include "max_value.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream in(argv[1]);

    int n = 0;
    in >> n;

    double* nums = new double[n];
    for (int i = 0; i < n; i++) {
        in >> nums[i];
    }

    in.close();

    double result = calculateMaxValue(nums, n);
    delete[] nums;

    ofstream out(argv[2]);
    out << result << endl;
    out.close();

    return 0;
}

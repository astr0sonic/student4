#include <fstream>
#include "volume.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream in(argv[1]);

    int a = 0, b = 0, c = 0;
    int n = 0;
    in >> a >> b >> c;
    in >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        in >> arr[i];
    }
    in.close();

    int result =  getMaxVolume(a, b, c, n, arr);

    ofstream out(argv[2]);
    out << result << endl;
    out.close();

    return 0;
}

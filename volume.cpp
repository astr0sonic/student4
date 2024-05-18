#include "volume.h"

int getMaxVolume(int a, int b, int c, int n, int* arr) {
    int max = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (((j - i) <= a) and (min(arr[i], arr[j]) <= c)) if ((b * (j - i) * min(arr[i], arr[j])) > max) max = b * (j - i) * min(arr[i], arr[j]);
    return max;
}
//10 a
//10 b
//10 c
//15 n
//19 8 8 7 18 16 6 17 10 11 10 19 3  17  3
//0  1 2 3 4 5 6 7  8  9 10 11 12 13 14 15
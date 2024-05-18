#include "volume.h"

int getMaxVolume(int a, int b, int c, int n, int* arr) {
    int max = 0;
    int min;
    for (int i = 0; i < n; i++) {//i = 1
        for (int j = i; j < n; j++) {//j = 0
            if (arr[i] < arr[j]) {//
                min = arr[i];
            }
            else {
                min = arr[j];//min = 10
            }
            if (((j - i) <= a) and (min <= c)) //0 <=10 and min <=10
            {
                if ((b * (j - i) * min) > max) // 10 * 10
                    max = b * (j - i) * min;//max = 10 * 100

            }
        }
    }
    return max;
}
//10 a
//10 b
//10 c
//15 n
//19 8 8 7 18 16 6 17 10 11 10 19 3  17  3
//0  1 2 3 4   5 6 7  8  9 10 11 12 13 14 15
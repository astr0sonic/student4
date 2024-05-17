#include "sundaram.h"
#include "vector"

std::vector<int> sieve(int n) {
    std::vector<int> primes;
    primes.push_back(2);
    if (n >= 3) primes.push_back(3);
    std::vector <int> arr(n + 1);
    for (int i = 2; i <= n; i++) arr[i] = i;

    for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++) if (i + j + 2 * i * j <= n) arr[i + j + 2 * i * j] = 0;
    int i = 1;
    while (2 * i + 1 <= n) {
        if (arr[i] != 0) primes.push_back(2 * i + 1);
        i++;
    }
    return primes;
}

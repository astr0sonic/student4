#include "eratosthenes.h"

std::vector<int> sieve(int n) {
    std::vector<int> primes;
    std::vector<int> arr(n + 1, 1);
    for (int p = 2; p * p <= n; ++p) {
        if (arr[p] == 1) {
            for (int j = p * p; j <= n; j += p) {
                arr[j] = 0;
            }
        }
    }
    for (int p = 2; p <= n; ++p) {
        if (arr[p] == 1) {
            primes.push_back(p);
        }
    }
    return primes;
}

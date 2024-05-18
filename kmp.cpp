#include "kmp.h"
#include "vector"

std::vector<int> getIndices(const std::string& my_template, const std::string& text) {
    std::vector<int> result;
    string s = my_template + "#" + text;
    int n = s.length();
    int t = text.length();
    int m = my_template.length();
    vector<int> pi(n, 0);
    int i = 1;
    int j = 0;
    while (i < n) {
        if (s[j] == s[i]) {
            pi[i] = j + 1;
            i++; j++;
        }
        else {
            if (j == 0) {
                pi[i] = 0;
                i++;
            }
            else j = pi[j - 1];
        }
    }
    for (int i = m + 1; i < n; i++) {
        if (pi[i] == m) result.push_back(i - 2 * m);
    }
    return result;
}

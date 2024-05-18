#include "max_value.h"
#include<queue>

double calculateMaxValue(double* nums, int n) {
    std::queue<double> q;
    q.push(nums[0]);
    for (int i = 1; i < n; i++) {
        int j = 0;
        int m = q.size();
        while (j < m){
            double first = q.front();
            q.pop();
            q.push(first + nums[i]);
            q.push(first - nums[i]);
            q.push(first * nums[i]);
            if (nums[i] != 0) q.push(first / nums[i]);
            j++;
        }
    }
    double max = q.front();
    q.pop();
    while (!q.empty()) {
        if (max < q.front()) max = q.front();
        q.pop();
    }
    return max;
}

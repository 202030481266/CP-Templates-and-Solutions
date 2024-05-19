#include <bits/stdc++.h>
using namespace std;

unsigned long long combination(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k > n - k) k = n - k; // C(n, k) == C(n, n-k)

    unsigned long long result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= n - (k - i);
        result /= i;
    }
    return result;
}

class Solution {
public:
    int waysToReachStair(int k) {
        // [0, i] 总共就是有 i 个间隔
        // 开始的位置是1并不是0
        int ans = 0;
        for (int i = 0; i < 31; ++i) {
            if ((1<<i) >= k && (1<<i) - i <= k) {
                int tmp = (1<<i) - k;
                // C(i, tmp)
                // 计算组合数
                ans += combination(i, tmp);
            }
            if ((1<<i) - 1 >= k && (1<<i) - 1 - i <= k) {
                int tmp = (1<<i) - 1 - k;
                // C(i, tmp)
                // 计算组合数
                ans += combination(i, tmp);
            }
        }
        return ans;
    }
};

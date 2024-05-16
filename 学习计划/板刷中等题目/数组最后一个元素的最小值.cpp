#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;
    long long minEnd(int n, int x) {
        // 就是找到最少的0的位数然后把它们做一个映射
        ll N = 1ll * n, X = 1ll * x;
        int msb = 63 - __builtin_clzll(X);
        vector<int> bits;
        for (int i = 0; i < msb; ++i) {
            if (!(X & (1ll<<i))) {
                bits.push_back(i);
            }
        }
        int b = bits.size(), c = 1;
        while ((1ll<<b) < N) {
            bits.push_back(msb + c);
            ++b;
            ++c;
        }
        N -= 1;
        for (int i = 0; i < 32; ++i) {
            if (N & (1ll<<i)) {
                X += (1ll<<bits[i]);
            }
        }
        return X;
    }
};

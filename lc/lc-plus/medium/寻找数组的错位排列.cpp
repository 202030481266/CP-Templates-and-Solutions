#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const int N = 1e6;
ll f[N+1],g[N+1];
bool flag = false;
class Solution {
public:
    void init() {
        f[2]=g[2]=1;
        for (int i = 3; i <= N; ++i) {
            f[i] = (i-1)*g[i-1]%mod;
            g[i] = (f[i-1]+(i-1)*g[i-1]%mod)%mod;
        }
    }
    int findDerangement(int n) {
        // 组合数学
        if (!flag) {
            init();
            flag = true;
        }
        return f[n];
    }
};
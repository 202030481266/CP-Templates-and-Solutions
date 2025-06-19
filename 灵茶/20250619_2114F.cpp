// https://codeforces.com/problemset/problem/2114/F
// dfs branch&bound 剪枝技巧，是NP完全问题划分的最为重要的算法
#include <bits/stdc++.h>

using namespace std;
static constexpr int inf = 0x3f3f3f3f;

int min_group_dfs(vector<int>& f, int mx) {
    sort(f.begin(), f.end(), greater<int>());      
    if (f.empty()) return 0;
    if (f[0] > mx)   return -1;                    

    const int n = (int)f.size();
    int best = n;                                  
    vector<long long> prod(n, 1);                  

    function<void(int,int)> dfs = [&](int idx, int used) {
        if (used >= best) return;                  // 剪枝①：已不优
        if (idx == n) { best = used; return; }     // 所有质因子都放完

        int p = f[idx];
        long long last = -1;                       // 对称剪枝：同乘积的组只尝试一次

        /* ① 尝试放进已有组 */
        for (int i = 0; i < used; ++i) {
            if (prod[i] == last) continue;         // 跳过等价状态
            if (prod[i] <= 1LL * mx / p) {         // 防溢出 + 还能放
                long long before = prod[i];
                prod[i] *= p;
                dfs(idx + 1, used);
                prod[i] = before;                  
                last = before;                     
            }
        }

        prod[used] = p;
        dfs(idx + 1, used + 1);
        prod[used] = 1;                            
    };

    dfs(0, 0);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;  cin >> t;
    int N = 0;
    vector<array<int, 3>> qs(t);
    for (int i = 0; i < t; ++i) {
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2];
        for (int j = 0; j < 3; ++j) N = max(N, qs[i][j]);
    }

    vector<bool> is_prime(N + 1, true);
    vector<int>  spf(N + 1);                     
    iota(spf.begin(), spf.end(), 0);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; 1LL * i * i <= N; ++i) {
        if (is_prime[i])
        for (int j = i * i; j <= N; j += i) {
            if (is_prime[j]) spf[j] = i;          
            is_prime[j] = false;
        }
    }

    auto cal = [&](int target, int mx) -> int {
        if (target == 1)       return 0;          
        if (target <= mx)      return 1;          

        vector<int> fac;
        int x = target;
        while (x > 1) {
            int p = spf[x];                       
            if (p == 0) p = x;                    
            fac.push_back(p);
            x /= p;
        }
        return min_group_dfs(fac, mx);            
    };

    for (auto& q : qs) {
        int x = q[0], y = q[1], k = q[2];
        int g = gcd(x, y);
        x /= g;  y /= g;

        int rx = cal(x, k);
        int ry = cal(y, k);

        if (rx == -1 || ry == -1) cout << -1 << '\n';
        else                      cout << rx + ry << '\n';
    }
}
// https://codeforces.com/problemset/problem/1580/B
// 记忆化搜索剪枝，刷表不好搞

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 100;
int n, m, k, mod;
int C[101][101];
int F[101];
int memo[101][101][101];

int dfs(int dep, int size, int need) {
    if (dep < 0) {
        if (need > 0) {
            return 0;
        }
        return F[size]; // 随便排
    }
    if (size == 0) {
        return 1;
    }
    
    int& p = memo[dep][size][need];
    if (p >= 0) {
        return p;
    }
    
    if (dep == 0) { // 这是我们要找的
        need--;
    }
    
    int res = 0;
    for (int leftSz = 0; leftSz < size; leftSz++) {
        int leftNeedMin = max(need - (size - 1 - leftSz), 0);
        int leftNeedMax = min(leftSz, need);
        
        for (int leftNeed = leftNeedMin; leftNeed <= leftNeedMax; leftNeed++) {
            int leftRes = dfs(dep - 1, leftSz, leftNeed);
            if (leftRes == 0) { // 剪枝，右子树不递归
                continue;
            }
            
            int rightRes = dfs(dep - 1, size - 1 - leftSz, need - leftNeed);
            long long contribution = (1LL * C[size-1][leftSz] * leftRes % mod * rightRes) % mod;
            res = (res + contribution) % mod;
        }
    }
    
    p = res;
    return res;
}

void cf1580B() {
    cin >> n >> m >> k >> mod;
    F[0] = 1;
    memset(memo, -1, sizeof(memo));
    for (int i = 1; i < maxn; i++) {
        F[i] = (1LL * F[i-1] * i) % mod;
    }
    for (int i = 0; i < maxn; i++) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
        }
    }
    cout << dfs(m - 1, n, k) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cf1580B();
    return 0;
}
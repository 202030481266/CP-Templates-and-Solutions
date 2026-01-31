#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int MAXN = 100005;
int lp[MAXN], flag;

// 考察质因数分解的技巧

void init() {
    flag = 1;
    for (int i = 1; i <= 100000; ++i) lp[i] = i;
    for (int i = 2; i * i <= 100000; ++i) {
        if (lp[i] == i) {
            for (int j = i * i; j <= 100000; j += i) lp[j] = i;
        }
    }
}

int cnt[MAXN], arr[MAXN];

class Solution {
public:
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        if (!flag) init();
        
        for (int i = 0; i < n; ++i) {
            vector<int> tmp;
            int x = nums[i];
            while (x > 1) {
                tmp.push_back(lp[x]);
                x /= lp[x];
            }
            for (int v : tmp) cnt[v]++;
            for (int v : tmp) {
                if (cnt[v] & 1) x *= v;
                cnt[v] = 0;
            }
            arr[i] = x;
        }
        
        vii g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        ll ans = 0; 
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            ans += cnt[arr[u]];
            ++cnt[arr[u]];
            for (int v : g[u]) {
                if (v != fa) {
                    self(self, v, u);
                }
            }
            --cnt[arr[u]];
        };
        
        dfs(dfs, 0, -1);
        return ans;
    }
};
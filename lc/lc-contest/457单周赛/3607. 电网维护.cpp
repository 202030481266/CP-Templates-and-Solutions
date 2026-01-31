#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;
int fa[maxn], mn[maxn], active[maxn]; 

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx > fy) swap(fx, fy);
    fa[fy] = fx;
}

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        for (int i = 1; i <= c; ++i) {
            fa[i] = i, active[i] = 1, mn[i] = 0;
        }
        for (auto& e : connections) {
            merge(e[0], e[1]);
        }
        for (auto& q : queries) {
            if (q[0] == 2) {
                active[q[1]]--;
            }
        }
        for (int i = c; i >= 1; --i) {
            if (active[i] > 0) {
                mn[find(i)] = i;
            }
        }
        vector<int> ans;
        for (int i = queries.size() - 1; i >= 0; --i) {
            int op = queries[i][0], x = queries[i][1], f = find(x);
            if (op == 2) {
                ++active[x];
                if (active[x] > 0) {
                    if (mn[f] == 0) mn[f] = x;
                    else mn[f] = min(mn[f], x);
                }
            }
            else {
                if (active[x] > 0) ans.push_back(x);
                else {
                    int res = mn[find(x)];
                    ans.push_back(res == 0 ? -1 : res);
                }
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
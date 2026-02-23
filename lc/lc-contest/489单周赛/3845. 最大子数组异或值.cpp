#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

struct Trie {
    int ch[40005 * 15][2];
    int sz[40005 * 15];
    int cnt;
    
    void init() {
        cnt = 1;
        ch[0][0] = ch[0][1] = 0;
        sz[0] = 0;
    }
    
    void insert(int x) {
        int u = 0;
        sz[u]++;
        for (int i = 14; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!ch[u][b]) {
                ch[cnt][0] = ch[cnt][1] = 0;
                sz[cnt] = 0;
                ch[u][b] = cnt++;
            }
            u = ch[u][b];
            sz[u]++;
        }
    }
    
    void remove(int x) {
        int u = 0;
        sz[u]--;
        for (int i = 14; i >= 0; i--) {
            int b = (x >> i) & 1;
            u = ch[u][b];
            sz[u]--;
        }
    }

    int queryMax(int x) {
        int u = 0, res = 0;
        for (int i = 14; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = 1 - b;
            if (ch[u][want] && sz[ch[u][want]] > 0) {
                res |= (1 << i);
                u = ch[u][want];
            } else {
                u = ch[u][b];
            }
        }
        return res;
    }

    int dfs(int u, int bit) {
        if (bit < 0) return 0;
        int l = ch[u][0], r = ch[u][1];
        bool hasL = l && sz[l] > 0;
        bool hasR = r && sz[r] > 0;
        if (hasL && hasR) {
            return (1 << bit) + maxXorBetween(l, r, bit - 1);
        } else {
            return dfs(hasL ? l : r, bit - 1);
        }
    }

    int maxXorBetween(int u, int v, int bit) {
        if (bit < 0) return 0;
        auto has = [&](int node, int b) {
            return ch[node][b] && sz[ch[node][b]] > 0;
        };
        int res = 0;
        if (has(u, 0) && has(v, 1))
            res = max(res, (1 << bit) + maxXorBetween(ch[u][0], ch[v][1], bit - 1));
        if (has(u, 1) && has(v, 0))
            res = max(res, (1 << bit) + maxXorBetween(ch[u][1], ch[v][0], bit - 1));
        if (res) return res;
        if (has(u, 0) && has(v, 0))
            res = max(res, maxXorBetween(ch[u][0], ch[v][0], bit - 1));
        if (has(u, 1) && has(v, 1))
            res = max(res, maxXorBetween(ch[u][1], ch[v][1], bit - 1));
        return res;
    }

    int queryAllMax() {
        if (sz[0] < 2) return 0;
        return dfs(0, 14);
    }
} trie;

class Solution {
public:
    int maxXor(vector<int>& nums, int k) {
        int n = nums.size();
        trie.init();
        vector<int> q1(n + 3); // 维护最小值
        vector<int> q2(n + 3); // 维护最大值
        vector<int> sum(n + 1);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] ^ nums[i];
        }
        int q1_l = 0, q1_r = 0;
        int q2_l = 0, q2_r = 0;
        int l = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            while (q1_r > q1_l && nums[q1[q1_r - 1]] >= nums[i]) --q1_r;
            q1[q1_r++] = i;
            while (q2_r > q2_l && nums[q2[q2_r - 1]] <= nums[i]) --q2_r;
            q2[q2_r++] = i;
            trie.insert(sum[i]);
            while (nums[q2[q2_l]] - nums[q1[q1_l]] > k) {
                if (q1[q1_l] == l) ++q1_l;
                if (q2[q2_l] == l) ++q2_l;
                trie.remove(sum[l]);
                l++;
            }
            ans = max(ans, trie.queryMax(sum[i + 1]));
        }
        return ans;
    }
};
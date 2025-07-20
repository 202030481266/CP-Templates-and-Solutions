#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int getLen(ull val) {
    int res = 0;
    while (val != 1u) {
        ++res;
        val = popcount(val);
    }
    return res;
}

static constexpr int maxn = 100005;
int fenwick[6][maxn], n;

inline int lowbit(int i) {
    return i & -i;
}

void update(int d, int p, int v) {
    while (p <= n) {
        fenwick[d][p] += v;
        p += lowbit(p);
    }
}

int query(int d, int p) {
    int res = 0;
    while (p > 0) {
        res += fenwick[d][p];
        p -= lowbit(p);
    }
    return res;
}

void add(ull v, int i) {
    int dep = getLen(v);
    if (dep <= 5) {
        update(dep, i, 1);
    }
}

void del(ull v, int i) {
    int dep = getLen(v);
    if (dep <= 5) {
        update(dep, i, -1);
    }
}

class Solution {
public:
    vector<int> popcountDepth(vector<long long>& nums, vector<vector<long long>>& queries) {
        n = nums.size();
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= 5; ++j) fenwick[j][i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            add((ull)nums[i-1], i);
        }
        vector<int> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                ans.push_back(query(q[3], q[2] + 1) - query(q[3], q[1]));
            }
            else {
                del((ull)nums[q[1]], q[1] + 1);
                nums[q[1]] = q[2];
                add((ull)nums[q[1]], q[1] + 1);
            }
        }
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;

int tree[maxn * 40][2];
int cnt[maxn * 40];
int tot;

void insert(int val, int i, int cur) {
    if (i < 0) {
        cnt[cur]++;
        return;
    }
    int b = (val >> i) & 1;
    if (!tree[cur][b]) {
        tree[cur][b] = ++tot;
        tree[tot][0] = tree[tot][1] = 0;
        cnt[tot] = 0;
    }
    insert(val, i - 1, tree[cur][b]);
    cnt[cur] = cnt[tree[cur][0]] + cnt[tree[cur][1]];
}

int cal(int val, int k) {
    int cur = 1; // root
    int ans = 0;
    for (int i = 30; i >= 0; --i) {
        int b = (val >> i) & 1, kb = (k >> i) & 1;
        if (!kb) ans += cnt[tree[cur][b ^ 1]];
        cur = tree[cur][kb ^ b];
    }
    return ans + cnt[cur];
}

class Solution {
public:
    long long countXorSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        tot = 1;
        cnt[tot] = 0;
        tree[tot][0] = tree[tot][1] = 0;

        int sum = 0;
        long long ans = 0;
        insert(0, 30, 1);
        for (int v : nums) {
            sum ^= v;
            ans += cal(sum, k);
            insert(sum, 30, 1);
        }
        return ans;
    }
};
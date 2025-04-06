#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e5 + 5;
int fa[maxn], l[maxn], r[maxn]; 
ll sum[maxn];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void init(int n) {
    for (int i = 0; i < n; ++i) {
        fa[i] = i;
        l[i] = i;
        r[i] = i;
        sum[i] = 0;
    }
}

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size(), cnt = 0, ans = 0;
        init(n);
        for (int i = 0; i < n; ++i) sum[i] = nums[i];
        set<tuple<ll,int,int>> s;
        for (int i = 0; i < n-1; ++i) {
            s.insert({nums[i]+nums[i+1], i, i+1});
            if (nums[i+1] < nums[i]) ++cnt;
        }
        while (cnt > 0) {
            auto [w, u, v] = *s.begin();
            s.erase(s.begin());
            int fu = find(u), fv = find(v);
            if (sum[fu] > sum[fv]) --cnt;
            if (l[fu] - 1 >= 0) {
                int fl = find(l[fu] - 1);
                s.erase(s.find({sum[fl] + sum[fu], fl, fu}));
                if (sum[fl] > sum[fu] && sum[fu] + sum[fv] >= sum[fl]) --cnt;
                if (sum[fl] <= sum[fu] && sum[fu] + sum[fv] < sum[fl]) ++cnt;
            }
            if (r[fv] + 1 < n) {
                int fr = find(r[fv] + 1);
                s.erase(s.find({sum[fv] + sum[fr], fv, fr}));
                if (sum[fv] > sum[fr] && sum[fu] + sum[fv] <= sum[fr]) --cnt;
                if (sum[fr] >= sum[fv] && sum[fu] + sum[fv] > sum[fr]) ++cnt;
            }
            ++ans;
            fa[fv] = fu;
            r[fu] = r[fv];
            sum[fu] += sum[fv];
            if (l[fu] - 1 >= 0) {
                int fl = find(l[fu] - 1);
                s.insert({sum[fl] + sum[fu], fl, fu});
            }
            if (r[fv] + 1 < n) {
                int fr = find(r[fv] + 1);
                s.insert({sum[fu] + sum[fr], fu, fr});
            }
        }
        return ans;
    }
};
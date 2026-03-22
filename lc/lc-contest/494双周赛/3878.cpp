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

struct node {
    int val, idx, ptr, last;
    node(int _v, int _id, int _p, int _last): val(_v), idx(_id), ptr(_p), last(_last) {}
    node(): val(0), idx(0), ptr(0), last(-1) {}
};
class Solution {
public:
    long long countGoodSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        vector<node> a;
        for (int i = 0; i < n; ++i) {
            a.push_back(node(0, i, i, -1));
            int k = 0;
            a[0].val |= nums[i];
            for (int j = 1; j < a.size(); ++j) {
                a[j].val |= nums[i];
                if (a[k].val == a[j].val) a[k].idx = a[j].idx;
                else a[++k] = a[j];
            }
            a.resize(k + 1); // [0, k]
            for (int i = k; i >= 0; --i) {
                if (a[i].last != -1 && nums[a[i].last] != a[i].val) a[i].last = -1;
                while (a[i].ptr <= a[i].idx) {
                    if (nums[a[i].ptr] == a[i].val) a[i].last = a[i].ptr;
                    ++a[i].ptr;
                }
                if (a[i].last != -1) {
                    int st = i == 0 ? -1 : a[i - 1].idx;
                    ans += a[i].last - st;
                }
            }
        }
        return ans;
    }
};
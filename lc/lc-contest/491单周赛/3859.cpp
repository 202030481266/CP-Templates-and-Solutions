#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int cnt1[MAXN], cnt2[MAXN], cnt3[MAXN];

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        int n = nums.size();
        if (1LL * k * m > n) return 0;
        ll ans = 0;
        int p1 = 0, p2 = 0, p3 = 0;
        int t1 = 0, t2 = 0, t3 = 0;
        for (int i = 0; i < n; ++i) {
            ++cnt1[nums[i]];
            ++cnt2[nums[i]];
            ++cnt3[nums[i]];
            if (cnt1[nums[i]] == 1) ++t1;
            if (cnt2[nums[i]] == 1) ++t2;
            if (cnt3[nums[i]] == m) ++t3;
            while (t1 > k) {
                --cnt1[nums[p1]];
                if (cnt1[nums[p1]] == 0) --t1;
                ++p1;
            }
            while (t2 >= k) {
                --cnt2[nums[p2]];
                if (cnt2[nums[p2]] == 0) --t2;
                ++p2;
            }
            // [p1, p2)
            while (p3 < p1) {
                --cnt3[nums[p3]];
                if (cnt3[nums[p3]] == m - 1) --t3;
                ++p3;
            }
            while (t3 >= k && p3 < p2) {
                --cnt3[nums[p3]];
                if (cnt3[nums[p3]] == m - 1) --t3;
                ++p3;
            }
            ans += p3 - p1;
        }
        for (int v : nums) cnt1[v] = cnt2[v] = cnt3[v] = 0;
        return ans;
    }
};
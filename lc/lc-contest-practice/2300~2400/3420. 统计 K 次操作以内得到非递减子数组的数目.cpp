#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pii> stack(n + 7);
        vector<ll> sum(n + 1);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + nums[i];
        }
        int l = 0, r = 0, ed = n;
        ll s = 0, ans = 0;
        auto f = [&](int id) -> ll {
            // [id, right), (id, right]
            ll right = (r == l + 1 ? ed : stack[r - 2].second);
            return (right - id) * nums[id] - (sum[right] - sum[id]);
        };
        for (int i = n - 1; i >= 0; --i) {
            while (l < r && stack[r - 1].first <= nums[i]) {
                s -= f(stack[r - 1].second);
                --r;
            }
            stack[r++] = {nums[i], i};
            s += f(i);
            while (s > k) {
                if (ed <= stack[l].second) {
                    l++;
                }
                s -= (stack[l].first - nums[ed-1]);
                ed--;
            }
            ans += (ed - i); // [i, ed)
        }
        return ans;
    }
};
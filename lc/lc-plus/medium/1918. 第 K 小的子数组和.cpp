#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class Solution {
public:
    int kthSmallestSubarraySum(vector<int>& nums, int k) {
        // nlogU
        int n = nums.size();

        // sum[r] - sum[l] <= s, sum[r] <= sum[l]+s
        // fenwick tree is useful , but nums[i] >= 0 so we can use the slide window

        auto check = [&](int val) -> bool {
            long long res = 0, s = 0;
            int l = 0;
            for (int i = 0; i < n; ++i) {
                s += nums[i];
                while (s > val) {
                    s -= nums[l++];
                }
                res += (i-l+1);
            }
            return res >= k;
        };

        ll l = 0, r = accumulate(nums.begin(), nums.end(), 0ll)+1; // (l,r) is not sure
        while (l + 1 < r) {
            ll mid = (l+r) >> 1;
            if (check(mid)) r = mid; // (l,mid) is not sure
            else l = mid; // (mid, r) is not sure
        }
        return r;
    }
};
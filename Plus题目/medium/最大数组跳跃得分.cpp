#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    ll maxScore(vector<int>& nums) {
        int n = nums.size();
        // greedy
        ll mx = nums[n-1], last = n-1, ans = 0;
        for (int i = n-2; i >= 0; --i) {
            if (nums[i] > mx) {
                ans += (last-i) * mx;
                mx = nums[i];
                last = i;
            }
        }
        if (last > 0) ans += last * mx;
        return ans;
    }
};

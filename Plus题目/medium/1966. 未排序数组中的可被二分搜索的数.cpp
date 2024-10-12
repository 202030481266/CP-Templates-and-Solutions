#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int binarySearchableNumbers(vector<int>& nums) {
        int n = nums.size();
        if (n==1) return 1;
        vector<int> mx(n), mn(n);
        mx[0] = nums[0];
        mn[n-1] = nums[n-1];
        for (int i = 1; i < n; ++i) mx[i] = max(mx[i-1], nums[i]);
        for (int i = n-2; i >= 0; --i) mn[i] = min(mn[i+1], nums[i]);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (i==0) {
                if (nums[i] < mn[1]) ++ans;
            }
            else if (i==n-1) {
                if (nums[i] > mx[n-2]) ++ans;
            }
            else {
                if (nums[i] > mx[i-1] && nums[i] < mn[i+1]) ++ans;
            }
        }
        return ans;
    }
};
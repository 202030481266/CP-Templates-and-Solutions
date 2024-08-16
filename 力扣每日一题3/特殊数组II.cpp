#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> arr;
        int n = nums.size();
        for (int i = 0; i+1 < n; ++i) {
            if ((nums[i] & 1) ^ (nums[i+1] & 1) == 0) arr.push_back(i) ;
        }
        vector<bool> ans;
        for (auto q : queries) {
            if (q[1] == q[0]) ans.push_back(true);
            else {
                int l = q[0], r = q[1]-1;
                // [l,r]
                auto it = lower_bound(arr.begin(), arr.end(), l);
                if (it != arr.end() && *it <= r) ans.push_back(false);
                else ans.push_back(true);
            }
        }
        return ans;
    }
};
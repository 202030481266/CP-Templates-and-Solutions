#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        int l = 0, pre = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] == pre+1) {
                ++pre;
            }
            else {
                // [l,i)
                // [i-k, i)
                for (int j=l; j<= i-k; ++j) ans.push_back(nums[j+k-1]);
                for (int j=max(l,i-k+1); j<i; ++j) ans.push_back(-1);
                l = i;
                pre = nums[i];
            }
        }
        // [l,n)
        // [n-k, n)
        for (int j=l; j<=n-k; ++j) ans.push_back(nums[j+k-1]);
        for (int j=max(l,n-k+1); j<n; ++j) ans.push_back(-1);
        ans.resize(n-k+1);
        return ans;
    }
};
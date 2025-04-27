#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> left(n);
        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i-1] > maxDiff) {
                left[i] = i;
            }
            else {
                left[i] = left[i-1];
            }
        }
        vector<bool> ans;
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            if (l > r) swap(l, r);
            ans.push_back(left[r] <= l);
        }
        return ans;
    }
};
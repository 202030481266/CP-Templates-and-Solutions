#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int a, int b) {
        multiset<int> left, right;
        // [a,n-1-a]
        int n = nums.size();
        if (a == 0) {
            int mn = 0, mx = 0;
            for (int i = 0; i < n; ++i) {
                if (nums[i] < nums[mn]) mn = i;
                if (nums[i] > nums[mx]) mx = i;
            }
            if (nums[mx] - nums[mn] >= b) return {mn, mx};
            else return {-1, -1};
        }
        auto f = [&](multiset<int>& s, int i, int st, int ed) -> int {
            auto x = s.lower_bound(nums[i] + b), y = s.upper_bound(nums[i] - b);
            if (x != s.end() || y != s.begin()) {
                for (int k = st; k < ed; ++k) {
                    if (abs(nums[k] - nums[i]) >= b) {
                        return k;
                    }
                }
            }
            return -1;
        };
        for (int i = a; i < n; ++i) right.insert(nums[i]);
        int res = -1;
        for (int i = 0; i < n; ++i) {
            if (right.size()) {
                res = f(right, i, i+a, n);
                if (res != -1) return {i, res};
            }
            if (left.size()) {
                res = f(left, i, 0, i-a+1);
                if (res != -1) return {i, res};
            }
            if (i-a >= 0) left.insert(nums[i-a]);
            if (i+a < n) right.erase(right.lower_bound(nums[i+a]));
        }
        return {-1,-1};
    }
};